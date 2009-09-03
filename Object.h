/* 
 * File:   Object.h
 * Author: mark
 *
 * Created on August 19, 2009, 7:10 PM
 */

#ifndef _OBJECT_H
#define	_OBJECT_H

#include <QtCore/QObject>
#include <QtGui/QGraphicsItem>
#include <Box2D/Box2D.h>
#include "Polygon.h"

class World;

class Object : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal    mass                READ mass);
    Q_PROPERTY(qreal    inertia             READ inertia);
    Q_PROPERTY(QPointF  position            READ position           WRITE setPosition);
    Q_PROPERTY(QPointF  linearVelocity      READ linearVelocity     WRITE setLinearVelocity);
    Q_PROPERTY(qreal    angle               READ angle              WRITE setAngle);
    Q_PROPERTY(qreal    angularVelocity     READ angularVelocity    WRITE setAngularVelocity);
    Q_PROPERTY(qreal    linearDamping       READ linearDamping      WRITE setLinearDamping);
    Q_PROPERTY(qreal    angularDamping      READ angularDamping     WRITE setAngularDamping);
    Q_PROPERTY(qreal    density             READ density            WRITE setDensity);
    Q_PROPERTY(qreal    friction            READ friction           WRITE setFriction);
    Q_PROPERTY(qreal    restitution         READ restitution        WRITE setRestitution);
    Q_PROPERTY(bool     isBullet            READ isBullet           WRITE setBullet);
    Q_PROPERTY(bool     isAllowedToSleep    READ isAllowedToSleep   WRITE setAllowedToSleep);
    Q_PROPERTY(bool     isSleeping          READ isSleeping         WRITE setSleeping);
    Q_PROPERTY(bool     isSensor            READ isSensor           WRITE setSensor);
    Q_PROPERTY(bool     isStatic            READ isStatic           WRITE setStatic);
    Q_PROPERTY(QColor   color               READ color              WRITE setColor);
    friend class World;
public:
    Object(const QPolygonF &poly = QPolygonF(), QObject *parent = NULL);

    // read
    QPointF position() const;
    qreal angle() const;
    QPointF linearVelocity() const;
    qreal angularVelocity() const;
    qreal mass() const;
    qreal inertia() const;
    qreal linearDamping() const;
    qreal angularDamping() const;
    bool isBullet() const;
    bool isAllowedToSleep() const;
    bool isSleeping() const;
    bool isStatic() const;
    qreal density() const;
    bool isSensor() const;
    qreal friction() const;
    qreal restitution() const;
    QColor color() const;

    // write
    void setPosition(const QPointF &pos);
    void setAngle(qreal angle);
    void setLinearVelocity(const QPointF &vel);
    void setAngularVelocity(qreal vel);
    void setLinearDamping(qreal damp);
    void setAngularDamping(qreal damp);
    void setBullet(bool flag);
    void setAllowedToSleep(bool flag);
    void setSleeping(bool flag);
    void setStatic(bool flag);
    void setDensity(qreal density);
    void setSensor(bool flag);
    void setFriction(qreal fric);
    void setRestitution(qreal rest);
    void setColor(const QColor &poly);

    // misc
    void touch() const;
    void paintGL() const;
    void setPolygon(const QPolygonF &poly);
    

signals:
    void propertyChanged() const;

private:
    b2Body *m_body;
    qreal m_density;
    QPolygonF m_poly;
    QColor m_color;
};



#endif	/* _OBJECT_H */

