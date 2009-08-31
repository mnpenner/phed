/* 
 * File:   LineStrip.h
 * Author: mark
 *
 * Created on August 30, 2009, 10:36 AM
 */

#ifndef _LINESTRIP_H
#define	_LINESTRIP_H

#include <qt4/QtGui/qgraphicsitem.h>
#include <qt4/QtGui/QPainter>

class LineStrip : public QGraphicsPolygonItem {
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void append(const QPointF& p);
    bool isEmpty() const;
    const QPointF& last() const;
private:
    QList<QPointF> points;
};

#endif	/* _LINESTRIP_H */

