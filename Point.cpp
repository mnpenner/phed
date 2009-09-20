/* 
 * File:   Point.cpp
 * Author: mark
 * 
 * Created on September 7, 2009, 1:00 AM
 */

#include "Point.h"

Point::Point() : QPointF() {}
Point::Point(qreal x, qreal y) : QPointF(x, y) {}
Point::Point(const QPoint& p) : QPointF(p) {}
Point::Point(const QPointF& p) : QPointF(p) {}
Point::Point(const b2Vec2& p) : QPointF(p.x, p.y) {}

Point::operator b2Vec2() const {
    return b2Vec2(x(), y());
}

qreal Point::lengthSquared() const {
    return x()*x() + y()*y();
}