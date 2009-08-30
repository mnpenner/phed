/* 
 * File:   EditorView.h
 * Author: mark
 *
 * Created on August 9, 2009, 6:57 PM
 */

#ifndef _EDITORVIEW_H
#define	_EDITORVIEW_H

#include <QtCore>
#include <QtOpenGL>
#include <Box2D/Box2D.h>
#include "Object.h"
#include "Polygon.h"

class EditorView : public QGLWidget {
    Q_OBJECT

public:
    EditorView(QWidget *parent = NULL);
    ~EditorView();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    void statusBarUpdate(const QString&); // TODO: rename to "request" or mouseMoved or something
    void objectsSelected(const QList<QObject*>&);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void showGrid(bool enabled);
    void useSelectionTool();
    void useCircleTool();
    void usePolygonTool();
    void useLineTool();
    void useRectangleTool();
    void pausePhysics();
    void runPhysics();

private slots:
    void updatePhys();

private:
    void initBox2D();
    void updateView();
    void drawGrid();
    void displayFPS();
    void drawPhys();
    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void drawPhysCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const QColor& color);
    void drawPhysPolygon(const b2Vec2* vertices, int32 vertexCount, const QColor& color);
    QPointF mouseToWorld(QPoint pos);
    qreal dist(qreal x1, qreal y1, qreal x2, qreal y2);

    enum Tool { SELECTION_TOOL, CIRCLE_TOOL, POLYGON_TOOL, RECTANGLE_TOOL, LINE_TOOL, NUM_TOOLS };

    QPointF viewPos;
    QPointF mousePos;
    QPoint lastMousePos;
    QSize winSize;
    double pixelsPerMeter;
    bool gridOn;
    Tool selectedTool;
    QVector<b2Vec2> tmpPoly; // TODO: change back to QPointF -- the decomposer can convert
    Polygon tmpPoly2;
    QList<Polygon> convParts;
    const double closePolyDist;
    const int physFPS;
    const int drawFPS;

    b2World *physWorld;
    QTimer *redrawTimer;
    QTimer *physTimer;
};

#endif	/* _EDITORVIEW_H */

