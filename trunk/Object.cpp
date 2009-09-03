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
#include <QtOpenGL/QtOpenGL>
#include "Object.h"

Object::Object(const QPolygonF& poly, QObject *parent) : QObject(parent), m_body(NULL), m_density(1.0), m_poly(poly), m_color(255,255,255)  {
}

void Object::setPolygon(const QPolygonF& poly) {
    Q_ASSERT_X(m_body == NULL, "setPolygon", "Polygon cannot be set after adding to World");
    m_poly = poly;
}

QColor Object::color() const {
    return m_color;
}

void Object::setColor(const QColor &col) {
    if(col != m_color) {
        m_color = col;
        emit propertyChanged();
    }
}

QPointF Object::position() const {
    Q_ASSERT(m_body != NULL);
    const b2Vec2 &p = m_body->GetPosition();
    return QPointF(p.x, p.y);
}

void Object::setPosition(const QPointF &pos) {
    Q_ASSERT(m_body != NULL);
    const b2Vec2 newPos = b2Vec2(pos.x(), pos.y());
    const b2Vec2 &oldPos = m_body->GetPosition();
    if((newPos.x != oldPos.x) || (newPos.y != oldPos.y)) {
        m_body->SetXForm(newPos, m_body->GetAngle());
        emit propertyChanged();
    }
}

qreal Object::angle() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetAngle();
}

void Object::setAngle(qreal ang) {
    Q_ASSERT(m_body != NULL);
    if(ang != angle()) {
        m_body->SetXForm(m_body->GetPosition(), ang);
        emit propertyChanged();
    }
}

QPointF Object::linearVelocity() const {
    Q_ASSERT(m_body != NULL);
    const b2Vec2 &v = m_body->GetLinearVelocity();
    return QPointF(v.x, v.y);
}

void Object::setLinearVelocity(const QPointF& vel) {
    Q_ASSERT(m_body != NULL);
    if(vel != linearVelocity()) {
        m_body->SetLinearVelocity(b2Vec2(vel.x(), vel.y()));
        emit propertyChanged();
    }
}

qreal Object::angularVelocity() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetAngularVelocity();
}

void Object::setAngularVelocity(qreal vel) {
    Q_ASSERT(m_body != NULL);
    if(vel != angularVelocity()) {
        m_body->SetAngularVelocity(vel);
        emit propertyChanged();
    }
}

qreal Object::angularDamping() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetAngularDamping();
}

void Object::setAngularDamping(qreal damp) {
    Q_ASSERT(m_body != NULL);
    if(damp != angularDamping()) {
        m_body->SetAngularDamping(damp);
        emit propertyChanged();
    }
}

qreal Object::linearDamping() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetLinearDamping();
}

void Object::setLinearDamping(qreal damp) {
    Q_ASSERT(m_body != NULL);
    if(damp != linearDamping()) {
        m_body->SetLinearDamping(damp);
        emit propertyChanged();
    }
}

bool Object::isBullet() const {
    Q_ASSERT(m_body != NULL);
    return m_body->IsBullet();
}

void Object::setBullet(bool flag) {
    Q_ASSERT(m_body != NULL);
    if(flag != isBullet()) {
        m_body->SetBullet(flag);
        emit propertyChanged();
    }
}

bool Object::isAllowedToSleep() const {
    Q_ASSERT(m_body != NULL);
    return m_body->IsAllowSleeping();
}

void Object::setAllowedToSleep(bool flag) {
    Q_ASSERT(m_body != NULL);
    if(flag != isAllowedToSleep()) {
        m_body->AllowSleeping(flag);
        emit propertyChanged();
    }
}

bool Object::isStatic() const {
    Q_ASSERT(m_body != NULL);
    return m_body->IsStatic();
}

void Object::setStatic(bool flag) {
    Q_ASSERT(m_body != NULL);
    if(flag != isStatic()) {
        if(flag) {
            if(density() != 0) m_density = density();
            setDensity(0);
        } else setDensity(m_density);
        emit propertyChanged();
    }
}

qreal Object::mass() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetMass();
}

qreal Object::inertia() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetInertia();
}

bool Object::isSleeping() const {
    Q_ASSERT(m_body != NULL);
    return m_body->IsSleeping();
}

void Object::setSleeping(bool flag) {
    Q_ASSERT(m_body != NULL);
    if(flag != isSleeping()) {
        if(flag) m_body->PutToSleep();
        else m_body->WakeUp();
        emit propertyChanged();
    }
}

bool Object::isSensor() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->IsSensor() : false;
}

void Object::setSensor(bool flag) {
    Q_ASSERT(m_body != NULL);
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
    Q_ASSERT(m_body != NULL);
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetDensity() : 0;
}

void Object::setDensity(qreal dens) {
    Q_ASSERT(m_body != NULL);
    if(dens != density()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetDensity(dens);
        }
        m_body->SetMassFromShapes();
        emit propertyChanged();
    }
}

qreal Object::friction() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetFriction() : 0;
}

void Object::setFriction(qreal fric) {
    Q_ASSERT(m_body != NULL);
    if(fric != friction()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetFriction(fric);
        }
        emit propertyChanged();
    }
}

qreal Object::restitution() const {
    Q_ASSERT(m_body != NULL);
    return m_body->GetFixtureList() ? m_body->GetFixtureList()->GetRestitution() : 0;
}

void Object::setRestitution(qreal rest) {
    Q_ASSERT(m_body != NULL);
    if(rest != restitution()) {
        for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
            f->SetRestitution(rest);
        }
        emit propertyChanged();
    }
}

void Object::paintGL() const {
    Q_ASSERT(m_body != NULL);
    const b2Transform& xf = m_body->GetTransform();

    for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
        b2Vec2 center;
        b2PolygonShape* poly;
        int32 vertexCount;
        b2Vec2 vertices[b2_maxPolygonVertices];

        switch(f->GetType()) {
            case b2Shape::e_polygon:
                poly = static_cast<b2PolygonShape*>(f->GetShape());
                vertexCount = poly->m_vertexCount;
                b2Assert(vertexCount <= b2_maxPolygonVertices);

                for(int32 i = 0; i < vertexCount; ++i) {
                    vertices[i] = b2Mul(xf, poly->m_vertices[i]);
                }

                glColor4ub(m_color.red(), m_color.green(), m_color.blue(), 64);
                glBegin(GL_POLYGON);
                for(int32 i = 0; i < vertexCount; ++i) {
                    glVertex2f(vertices[i].x, vertices[i].y);
                }
                glEnd();

                glColor4ub(m_color.red(), m_color.green(), m_color.blue(), 255);
                glBegin(GL_LINE_LOOP);
                for(int32 i = 0; i < vertexCount; ++i) {
                    glVertex2f(vertices[i].x, vertices[i].y);
                }
                glEnd();
                break;
            default:
                break;
        }
    }
}