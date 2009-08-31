/* 
 * File:   EditorView.h
 * Author: mark
 *
 * Created on August 30, 2009, 1:26 PM
 */

#ifndef _EDITORVIEW_H
#define	_EDITORVIEW_H

#include <QtGui/QGraphicsView>

class EditorView : public QGraphicsView {
public:
    EditorView(QGraphicsScene *scene, QWidget *parent = NULL);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
private:
    QPointF m_lastMousePos;
    QCursor m_lastCursor;
};

#endif	/* _EDITORVIEW_H */

