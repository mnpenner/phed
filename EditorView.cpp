/* 
 * File:   EditorView.cpp
 * Author: mark
 * 
 * Created on August 9, 2009, 6:57 PM
 */

#include <QtGui/QMouseEvent>
#include <QtGui/QFont>
#include <QtCore>
#include <algorithm>
#include "EditorView.h"
#include "EditorWindow.h"
#include "FixtureQuery.h"
#include "Object.h"

EditorView::EditorView(QWidget *parent)
: QGLWidget(parent), pixelsPerMeter(50), gridOn(false), closePolyDist(7.5), physFPS(30), drawFPS(200) {
    redrawTimer = new QTimer(this);
    connect(redrawTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    redrawTimer->start(1000 / drawFPS);

    physTimer = new QTimer(this);
    connect(physTimer, SIGNAL(timeout()), this, SLOT(updatePhys()));
    physTimer->setInterval(1000 / physFPS);

    setMouseTracking(true);
    initBox2D();
}

void partitionObjectFromFile(QString filename) {
    QFile file(filename);
    QTime timer;
    int elapsed;
    Polygon poly;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        qreal x, y;
        while(!stream.atEnd()) {
            stream >> x >> y;
            poly.append(QPointF(x,y));
        }
        poly.pop_back();
    }
    poly = poly.ccw();
    QList<Polygon> parts;
    timer.start();
    for(int i=0; i<10; ++i) {
        parts = poly.decomp();
    }
    elapsed = timer.elapsed();
    printf("partitioned into %d polygons in %f ms\n", parts.size(), elapsed/10.0);
}

EditorView::~EditorView() {
    delete physWorld;
}

void EditorView::initializeGL() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    winSize = size();
    viewPos = QPointF(-width() / 2 / pixelsPerMeter, -height() / 2 / pixelsPerMeter);
    updateView();
}

void EditorView::resizeGL(int w, int h) {
    QSize growth = size() - winSize;
    viewPos.ry() -= growth.height() / pixelsPerMeter;
    glViewport(0, 0, w, h);
    updateView();
    winSize = size();
}

void EditorView::initBox2D() {
    const b2Vec2 gravity(0, -9.80665);
    const bool doSleep = true;
    physWorld = new b2World(gravity, doSleep);
}

void EditorView::updatePhys() {
    const float timeStep = 1 / (1000 / floor(1000 / physFPS));
    const int velocityIterations = 8;
    const int positionIterations = 1;
    physWorld->Step(timeStep, velocityIterations, positionIterations);

    if(!Object::selectedObjects.isEmpty()) {
        ((Object*)Object::selectedObjects.first())->touch();
    }
}

void EditorView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);

    drawPhys();

    if(selectedTool == POLYGON_TOOL && tmpPoly2.size() > 0) {
        glLineWidth(2);
        glColor3ub(0, 255, 0);
        glBegin(GL_LINE_STRIP);

        foreach(QPointF p, tmpPoly2) {
            glVertex2f(p.x(), p.y());
        }
        glEnd();

        glColor4ub(0, 255, 0, 128);
        glBegin(GL_LINES);
        glVertex2f(tmpPoly2.last().x(), tmpPoly2.last().y());
        glVertex2f(mousePos.x(), mousePos.y());
        glEnd();

        if(tmpPoly2.size() > 2) {
            if(dist(mousePos.x(), mousePos.y(), tmpPoly2.first().x(), tmpPoly2.first().y()) * pixelsPerMeter <= closePolyDist) {
                glColor3ub(255, 255, 255);
                glLineWidth(1.5);
                drawCircle(tmpPoly2.first().x(), tmpPoly2.first().y(), closePolyDist / pixelsPerMeter);
            }
        }
    }

    glColor3ub(255,0,0);
    foreach(Polygon poly, convParts) {
        glBegin(GL_LINE_LOOP);
        foreach(QPointF p, poly) {
            glVertex2f(p.x(), p.y());
        }
        glEnd();
    }
    

    if(gridOn) drawGrid();
    displayFPS();
}

void EditorView::drawPhys() {
    for(b2Body* b = physWorld->GetBodyList(); b; b = b->GetNext()) {
        const b2Transform& xf = b->GetTransform();
        QColor color;
        if(b->IsStatic()) {
            color.setRgbF(0.5f, 0.9f, 0.5f);
        } else if(b->IsSleeping()) {
            color.setRgbF(0.9f, 0.9f, 0.5f);
        } else {
            color.setRgbF(0.5f, 0.5f, 0.9f);
        }
        for(b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()) {
            b2Vec2 center;
            float32 radius;
            b2Vec2 axis;
            b2CircleShape* circle;
            b2PolygonShape* poly;
            int32 vertexCount;
            b2Vec2 vertices[b2_maxPolygonVertices];
            switch(f->GetType()) {
                case b2Shape::e_circle:
                            circle = (b2CircleShape*) f->GetShape();

                    center = b2Mul(xf, circle->m_p);
                    radius = circle->m_radius;
                    axis = xf.R.col1;

                    drawPhysCircle(center, radius, axis, color);
                    break;
                case b2Shape::e_polygon:
                            poly = (b2PolygonShape*) f->GetShape();
                    vertexCount = poly->m_vertexCount;
                    b2Assert(vertexCount <= b2_maxPolygonVertices);

                    for(int32 i = 0; i < vertexCount; ++i) {
                        vertices[i] = b2Mul(xf, poly->m_vertices[i]);
                    }

                    drawPhysPolygon(vertices, vertexCount, color);
                    break;
                default:
                    break;
            }
        }
    }
}

void EditorView::drawCircle(GLfloat x, GLfloat y, GLfloat r) {
    static const double inc = M_PI / 12;
    static const double max = 2 * M_PI;
    glBegin(GL_LINE_LOOP);
    for(double d = 0; d < max; d += inc) {
        glVertex2f(cos(d) * r + x, sin(d) * r + y);
    }
    glEnd();
}

void EditorView::drawGrid() {
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1);
    glColor4ub(128, 128, 128, 128);
    float xMin, xMax, yMin, yMax;

    // vertical lines
    glBegin(GL_LINES);
    xMin = ceil(viewPos.x());
    xMax = floor(viewPos.x() + width() / pixelsPerMeter);
    yMin = viewPos.y();
    yMax = viewPos.y() + height() / pixelsPerMeter;
    for(int i = xMin; i <= xMax; ++i) {
        glVertex2f(i, yMin);
        glVertex2f(i, yMax);
    }
    glEnd();

    // horizontal lines
    glBegin(GL_LINES);
    xMin = viewPos.x();
    xMax = viewPos.x() + width() / pixelsPerMeter;
    yMin = ceil(viewPos.y());
    yMax = floor(viewPos.y() + height() / pixelsPerMeter);
    for(int i = yMin; i <= yMax; ++i) {
        glVertex2f(xMin, i);
        glVertex2f(xMax, i);
    }
    glEnd();
}

void EditorView::displayFPS() {
    glColor3ub(255, 255, 255);
    static int frameCount = 0;
    static float frameRate = 0;
    static QTime fpsTimer;
    if(fpsTimer.elapsed() > 1000) {
        frameRate = frameCount * 1000 / (float) fpsTimer.elapsed();
        fpsTimer.restart();
        frameCount = 0;
    }
    ++frameCount;
    renderText(5, 15, tr("%1").arg(frameRate, 0, 'f', 2));
}

QPointF EditorView::mouseToWorld(QPoint pos) {
    return QPointF(pos.x() / pixelsPerMeter + viewPos.x(), (height() - pos.y()) / pixelsPerMeter + viewPos.y());
}

void EditorView::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::MidButton) {
        lastMousePos = event->pos();
    } else if(event->button() == Qt::LeftButton) {
        if(selectedTool == POLYGON_TOOL) {
            if(tmpPoly2.size() > 2 && dist(mousePos.x(), mousePos.y(), tmpPoly2.first().x(), tmpPoly2.first().y()) * pixelsPerMeter <= closePolyDist) {
                Object *obj = new Object(physWorld, tmpPoly2);
                Object::objectList.append(obj);
                tmpPoly2.clear();
                Object::selectedObjects.clear();
                Object::selectedObjects.append(obj);
                emit objectsSelected(Object::selectedObjects);
            } else {
                tmpPoly2.append(mousePos);
            }
        } else if(selectedTool == SELECTION_TOOL) {
            const float eps = 0.005;
            b2AABB aabb;
            FixtureQuery fq;
            aabb.lowerBound = b2Vec2(mousePos.x() - eps, mousePos.y() - eps);
            aabb.upperBound = b2Vec2(mousePos.x() + eps, mousePos.y() + eps);
            Object::selectedObjects.clear();
            physWorld->Query(&fq, aabb);
            emit objectsSelected(Object::selectedObjects);
        }
    } else if(event->button() == Qt::RightButton) {
        switch(selectedTool) {
            case POLYGON_TOOL:
                if(!tmpPoly2.isEmpty()) {
                    tmpPoly2.pop_back();
                }
                break;
            default:
                break;
        }
    }
}

void EditorView::wheelEvent(QWheelEvent *event) {
    double scaleFactor = event->delta() / 100.;
    QSizeF oldSize(width() / pixelsPerMeter, height() / pixelsPerMeter);

    if(event->delta() > 0) pixelsPerMeter *= scaleFactor;
    else pixelsPerMeter /= -scaleFactor;

    QSizeF newSize(width() / pixelsPerMeter, height() / pixelsPerMeter);
    QSizeF deltaSize = newSize - oldSize;
    QPointF mousePos(event->x() / (qreal) width(), event->y() / (qreal) height());

    viewPos.rx() -= deltaSize.width() * mousePos.x();
    viewPos.ry() -= deltaSize.height() * (1 - mousePos.y());

    updateView();
}

void EditorView::updateView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(viewPos.x(), viewPos.x() + width() / pixelsPerMeter,
            viewPos.y(), viewPos.y() + height() / pixelsPerMeter);
    glMatrixMode(GL_MODELVIEW);
}

void EditorView::mouseMoveEvent(QMouseEvent *event) {
    mousePos = mouseToWorld(event->pos());
    emit statusBarUpdate(
            tr("%1, %2")
            .arg(mousePos.x(), 0, 'f', 2)
            .arg(mousePos.y(), 0, 'f', 2));
    if(event->buttons() & Qt::MidButton) {
        QPoint diff = event->pos() - lastMousePos;
        viewPos.rx() -= diff.x() / pixelsPerMeter;
        viewPos.ry() += diff.y() / pixelsPerMeter;
        lastMousePos = event->pos();
        updateView();
    }
}

QSize EditorView::minimumSizeHint() const {
    return QSize(160, 120);
}

QSize EditorView::sizeHint() const {
    return QSize(800, 600);
}

void EditorView::showGrid(bool enabled) {
    gridOn = enabled;
}

void EditorView::useCircleTool() {
    selectedTool = CIRCLE_TOOL;
    setCursor(Qt::CrossCursor);
}

void EditorView::useSelectionTool() {
    selectedTool = SELECTION_TOOL;
    setCursor(Qt::ArrowCursor);
}

void EditorView::usePolygonTool() {
    selectedTool = POLYGON_TOOL;
    setCursor(Qt::CrossCursor);
}

void EditorView::useLineTool() {
    selectedTool = RECTANGLE_TOOL;
    setCursor(Qt::CrossCursor);
}

void EditorView::useRectangleTool() {
    selectedTool = LINE_TOOL;
    setCursor(Qt::CrossCursor);
}

void EditorView::drawPhysCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const QColor& color) {
    const float32 k_segments = 16.0f;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;

    glColor4ub(color.red() / 2, color.green() / 2, color.blue() / 2, 128);
    glBegin(GL_POLYGON);
    for(int32 i = 0; i < k_segments; ++i) {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();

    theta = 0.0f;
    glColor4ub(color.red(), color.green(), color.blue(), 255);
    glBegin(GL_LINE_LOOP);
    for(int32 i = 0; i < k_segments; ++i) {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();

    b2Vec2 p = center + radius * axis;
    glBegin(GL_LINES);
    glVertex2f(center.x, center.y);
    glVertex2f(p.x, p.y);
    glEnd();
}

void EditorView::drawPhysPolygon(const b2Vec2* vertices, int32 vertexCount, const QColor& color) {
    glColor4ub(color.red() / 2, color.green() / 2, color.blue() / 2, 128);
    glBegin(GL_POLYGON);
    for(int32 i = 0; i < vertexCount; ++i) {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();

    glColor4ub(color.red(), color.green(), color.blue(), 255);
    glBegin(GL_LINE_LOOP);
    for(int32 i = 0; i < vertexCount; ++i) {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

qreal EditorView::dist(qreal x1, qreal y1, qreal x2, qreal y2) {
    qreal dx = x2 - x1;
    qreal dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void EditorView::runPhysics() {
    physTimer->start();
}

void EditorView::pausePhysics() {
    physTimer->stop();
}