/* 
 * File:   LineStrip.cpp
 * Author: mark
 * 
 * Created on August 30, 2009, 10:36 AM
 */

#include <qt4/QtGui/qgraphicssceneevent.h>

#include "LineStrip.h"

QRectF LineStrip::boundingRect() const {
    return m_poly.boundingRect();
}

void LineStrip::append(const QPointF& p) {
    m_poly.append(p);
    prepareGeometryChange();
}

bool LineStrip::isEmpty() const {
    return m_poly.isEmpty();
}

const QPointF& LineStrip::last() const {
    return m_poly.last();
}

void LineStrip::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->drawPolyline(m_poly);
}