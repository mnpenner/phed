/* 
 * File:   Point.h
 * Author: mark
 *
 * Created on September 7, 2009, 1:00 AM
 */

#ifndef _POINT_H
#define	_POINT_H

#include <QtCore/QPointF>
#include <Box2D/Common/b2Math.h>

class Point : public QPointF {
public:
    Point();
    Point(qreal x, qreal y);
    Point(const QPoint &p);
    Point(const QPointF &p);
    Point(const b2Vec2 &p);
    qreal lengthSquared() const;
    operator b2Vec2() const;
};

#endif	/* _POINT_H */

