/*
 * File:   EditorView.cpp
 * Author: mark
 *
 * Created on August 30, 2009, 1:26 PM
 */

#include <qt4/QtCore/qcoreevent.h>
#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <qt4/QtGui/qabstractslider.h>
#include "EditorView.h"

EditorView::EditorView(World *world, QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent), m_world(world), m_pixelsPerMeter(50) {
    setMouseTracking(true);
}

void EditorView::mousePressEvent(QMouseEvent* event) {

}

void EditorView::mouseMoveEvent(QMouseEvent* event) {
    emit mousePosChanged(mapToWorld(event->pos()));
}

void EditorView::mouseReleaseEvent(QMouseEvent* event) {

}

void EditorView::wheelEvent(QWheelEvent* event) {
    
}

void EditorView::resizeEvent(QResizeEvent* event) {
    QSize diff = size() - event->oldSize();
    m_viewPos.ry() -= diff.height() / m_pixelsPerMeter; // anchor view at top left when resizing
    glViewport(0, 0, width(), height());
    updatePM();
   
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
    m_viewPos = QPointF(-width() / 2 / m_pixelsPerMeter, 
            -height() / 2 / m_pixelsPerMeter); // width and height aren't set correctly until this point
    updatePM();
}

void EditorView::paintGL() {
    glColor4ub(255,255,255,128);
    glBegin(GL_POLYGON);
    {
        glVertex2f(-3,-3);
        glVertex2f(3,-3);
        glVertex2f(3,3);
    }
    glEnd();
   
}

void EditorView::updatePM() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(m_viewPos.x(), m_viewPos.x() + width() / m_pixelsPerMeter,
            m_viewPos.y(), m_viewPos.y() + height() / m_pixelsPerMeter);
    glMatrixMode(GL_MODELVIEW);
    
}

QPointF EditorView::mapToWorld(QPoint pos) const {
    return QPointF(pos.x() / m_pixelsPerMeter + m_viewPos.x(), (height() - pos.y()) / m_pixelsPerMeter + m_viewPos.y());
}

/*
void EditorView::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::MidButton) {
        m_lastMousePos = mapToScene(event->pos());
        m_lastCursor = cursor();
        setCursor(Qt::ClosedHandCursor);
    } else {
        QGraphicsView::mousePressEvent(event); // propogate
    }
}

void EditorView::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::MidButton) {
        setCursor(m_lastCursor);
    } else {
        QGraphicsView::mouseReleaseEvent(event); // propogate
    }
}

void EditorView::wheelEvent(QWheelEvent* event) {
    qreal factor;
    if(event->delta() > 0) factor = event->delta() / 100.;
    else factor = -100. / event->delta();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(factor, factor); // TODO: cap when whole scene is visible
}

void EditorView::mouseMoveEvent(QMouseEvent* event) {
    if(event->buttons() & Qt::MidButton) {
        QPointF pos = mapToScene(event->pos());
        QPointF diff = pos - m_lastMousePos;
        setTransformationAnchor(QGraphicsView::NoAnchor);
        translate(diff.x(), diff.y());
    }
    QGraphicsView::mouseMoveEvent(event); // propogate
}
 */