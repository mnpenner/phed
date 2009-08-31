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

EditorView::EditorView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) {
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::NoDrag);
    scale(1.0, -1.0); // flip coordinate system so that y increases upwards
    fitInView(-5, -5, 10, 10, Qt::KeepAspectRatio);
    setInteractive(true);
    setBackgroundBrush(QBrush(QColor(232,232,232), Qt::DiagCrossPattern));
}

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
    scale(factor, factor);
}

void EditorView::mouseMoveEvent(QMouseEvent* event) {
    if(event->buttons() & Qt::MidButton) {
        QPointF pos = mapToScene(event->pos());
        QPointF diff = pos - m_lastMousePos;
        setTransformationAnchor(QGraphicsView::NoAnchor);
        translate(diff.x(), diff.y());
        //m_lastMousePos = pos;
    }
    QGraphicsView::mouseMoveEvent(event); // propogate
}