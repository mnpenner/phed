/* 
 * File:   Polygon.h
 * Author: mark
 *
 * Created on August 26, 2009, 1:07 PM
 */

#ifndef _POLYGON_H
#define	_POLYGON_H

#include <QtGui/QPolygonF>

class Polygon : public QPolygonF {
public:

    Polygon();
    Polygon(int size);
    Polygon(const QPolygonF & polygon);
    Polygon(const QVector<QPointF> & points);
    Polygon(const QRectF & rectangle);
    Polygon(const QPolygon & polygon);
    const QPointF& at(int i) const;
    Polygon ccw() const;
    Polygon copy(int i, int j) const;
    bool isCW() const;
    bool canSee(int i, int j) const;
    bool isConvex() const;
    bool left(int i) const;
    bool leftOn(int i) const;
    bool right(int i) const;
    bool rightOn(int i) const;
    bool collinear(int i) const;
    bool reflex(int i) const;
    QList<Polygon> decomp() const;
    static bool left(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool leftOn(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool right(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool rightOn(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool collinear(const QPointF &a, const QPointF &b, const QPointF &c);
    static qreal area(const QPointF &a, const QPointF &b, const QPointF &c);
    static qreal sqdist(const QPointF &a, const QPointF &b);
};



#endif	/* _POLYGON_H */

