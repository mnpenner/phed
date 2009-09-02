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
    EditorView(World *world, QWidget *parent = NULL);
    QPointF mapToWorld(QPoint pos) const;

signals:
    void mousePosChanged(const QPointF&);
    
protected:
    void initializeGL();
    void paintGL();
    void updatePM();

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent *event);

private:
    World *m_world;
    QPoint m_lastMousePos;
    QCursor m_lastCursor;
    qreal m_pixelsPerMeter;
    QPointF m_viewPos;
    QTimer *m_redrawTimer;
    int m_drawFPS;
};

#endif	/* _EDITORVIEW_H */

