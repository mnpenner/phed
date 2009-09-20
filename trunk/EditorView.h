/* 
 * File:   EditorView.h
 * Author: mark
 *
 * Created on August 30, 2009, 1:26 PM
 */

#ifndef _EDITORVIEW_H
#define	_EDITORVIEW_H

#include <QtGui/QGraphicsView>
#include <QtOpenGL/QtOpenGL>
#include "World.h"

class EditorView : public QGLWidget {
    Q_OBJECT
    
public:
    enum Tool {
        Select, Scroll, Lasso, Measure,
        Pencil, Pen, Brush, Ellipse, Polygon, Rectangle, EdgeChain,
        RevoluteJoint, PulleyJoint, PrismaticJoint, LineJoint, GearJoint
    };

    EditorView(World *world, QWidget *parent = NULL);
    QPointF mapToWorld(QPoint pos) const;

signals:
    void mousePosChanged(const QPointF&);
    
public slots:
    void setTool(Tool tool);
    void showGrid(bool enabled);

protected:
    void initializeGL();
    void paintGL();
    void updatePM();

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent* event);

    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void drawGrid();
    void closePoly();

private:
    Tool m_tool;
    World *m_world;
    QPointF m_lastMousePos;
    QPointF m_mousePos;
    QPointF m_viewPos;
    QCursor m_lastCursor;
    QTimer m_redrawTimer;
    QPolygonF m_tmpPoly;
    QColor m_tmpColor;
    bool m_showGrid;
    bool m_readyClosePoly;
    int m_drawFPS;
    qreal m_pixelsPerMeter;
    qreal m_closePolyDist;
};

#endif	/* _EDITORVIEW_H */

