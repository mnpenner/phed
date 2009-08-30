/* 
 * File:   Object.cpp
 * Author: mark
 * 
 * Created on August 19, 2009, 7:10 PM
 */

#include <QtCore/QSharedPointer>
#include <qt4/QtGui/qgraphicsitem.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "Object.h"

Object::Object(b2World* world, const QPolygonF& poly) : m_density(1.0) {
    // Box2D
    QVector<b2Vec2> vertices(poly.size());
    for(int i = 0; i < poly.size(); ++i) {
        vertices[i] = b2Vec2(poly[i].x(), poly[i].y());
    }
    
    b2PolygonShape ps;
    ps.Set(&vertices[0], vertices.size());
    
    b2FixtureDef fd;
    fd.density = m_density;
    fd.shape = &ps;
    
    b2BodyDef bd;
    m_body = world->CreateBody(&bd);
    m_body->CreateFixture(&fd);
    m_body->SetUserData(this);
    m_body->SetMassFromShapes();
    
    // QGraphicsPolygonItem
    setPolygon(poly);
}

QPointF Object::position() const {
    const b2Vec2 &p = m_body->GetPosition();
    return QPointF(p.x, p.y);
}

void Object::setPosition(const QPointF &pos) {
    const b2Vec2 newPos = b2Vec2(pos.x(), pos.y());
    const b2Vec2 &oldPos = m_body->GetPosition();
    if((newPos.x != oldPos.x) || (newPos.y != oldPos.y)) {
        m_body->SetXForm(newPos, m_body->GetAngle());
        emit propertyChanged();
    }
}

qreal Object::angle() const {
    return m_body->GetAngle();
}

void Object::setAngle(qreal ang) {
    if(ang != angle()) {
        m_body->SetXForm(m_body->GetPosition(), ang);
        emit propertyChanged();
    }
}

QPointF Object::linearVelocity() const {
    const b2Vec2 &v = m_body->GetLinearVelocity();
    return QPointF(v.x, v.y);
}

void Object::setLinearVelocity(const QPointF& vel) {
    if(vel != linearVelocity()) {
        m_body->SetLinearVelocity(b2Vec2(vel.x(), vel.y()));
        emit propertyChanged();
    }
}

qreal Object::angularVelocity() const {
    return m_body->GetAngularVelocity();
}

void Object::setAngularVelocity(qreal vel) {
    if(vel != angularVelocity()) {
        m_body->SetAngularVelocity(vel);
        emit propertyChanged();
    }
}

qreal Object::angularDamping() const {
    return m_body->GetAngularDamping();
}

void Object::setAngularDamping(qreal damp) {
    if(damp != angularDamping()) {
        m_body->SetAngularDamping(damp);
        emit propertyChanged();
    }
}

qreal Object::linearDamping() const {
    return m_body->GetLinearDamping();
}

void Object::setLinearDamping(qreal damp) {
    if(damp != linearDamping()) {
        m_body->SetLinearDamping(damp);
        emit propertyChanged();
    }
}

bool Object::isBullet() const {
    return m_body->IsBullet();
}

void Object::setBullet(bool flag) {
    if(flag != isBullet()) {
        m_body->SetBullet(flag);
        emit propertyChanged();
    }
}

bool Object::isAllowedToSleep() const {
    return m_body->IsAllowSleeping();
}

void Object::setAllowedToSleep(bool flag) {
    if(flag != isAllowedToSleep()) {
        m_body->AllowSleeping(flag);
        emit propertyChanged();
    }
}

bool Object::isStatic() const {
    return m_body->IsStatic();
}

void Object::setStatic(bool flag) {
    if(flag != isStatic()) {
        if(flag) {
            if(density() != 0) m_density = density();
            setDensity(0);
        } else setDensity(m_density);
        emit propertyChanged();
    }
}

qreal Object::mass() const {
    return m_body->GetMass();
}

qreal Object::inertia() const {
    return m_body->GetInertia();
}

bool Object::isSleeping() const {
    return m_body->IsSleeping();
}

void Object::setSleeping(bool flag) {
    if(flag != isSleeping()) {
        if(flag) m_body->PutToSleep();
        else m_body->WakeUp();
        emit propertyChanged();
    }
}

bool Object::isSensor() const {
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->IsSensor() : false;
}

void Object::setSensor(bool flag) {
    if(flag != isSensor()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetSensor(flag);
        }
        emit propertyChanged();
    }
}

void Object::touch() const {
    emit propertyChanged();
}

qreal Object::density() const {
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetDensity() : 0;
}

void Object::setDensity(qreal dens) {
    if(dens != density()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetDensity(dens);
        }
        m_body->SetMassFromShapes();
        emit propertyChanged();
    }
}

qreal Object::friction() const {
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetFriction() : 0;
}

void Object::setFriction(qreal fric) {
    if(fric != friction()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetFriction(fric);
        }
        emit propertyChanged();
    }
}

qreal Object::restitution() const {
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetRestitution() : 0;
}

void Object::setRestitution(qreal rest) {
    if(rest != restitution()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetRestitution(rest);
        }
        emit propertyChanged();
    }
}