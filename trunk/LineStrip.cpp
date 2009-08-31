/* 
 * File:   LineStrip.cpp
 * Author: mark
 * 
 * Created on August 30, 2009, 10:36 AM
 */

#include <qt4/QtGui/qgraphicssceneevent.h>

#include "LineStrip.h"

QRectF LineStrip::boundingRect() const {
    if(points.isEmpty()) return QRectF();
    QPointF tl = points.first();
    QPointF br = points.last();
    foreach(QPointF p, points) {
        if(p.x() < tl.x()) tl.setX(p.x());
        if(p.y() > tl.y()) tl.setY(p.y());
        if(p.x() > br.x()) br.setX(p.x());
        if(p.y() < br.y()) br.setY(p.y());
    }
    return QRectF(tl, br);
}

void LineStrip::append(const QPointF& p) {
    points.append(p);
    prepareGeometryChange();
}

bool LineStrip::isEmpty() const {
    return points.isEmpty();
}

const QPointF& LineStrip::last() const {
    return points.last();
}

void LineStrip::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    for(int i = 1; i < points.size(); ++i) {
        painter->drawLine(points[i - 1], points[i]);
    }
}