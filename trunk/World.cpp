/* 
 * File:   World.cpp
 * Author: mark
 * 
 * Created on August 31, 2009, 6:32 PM
 */

#include "World.h"
#include "Object.h"

World::World(const QPointF& gravity, bool doSleep, QObject *parent)
: QObject(parent), m_world(b2Vec2(gravity.x(), gravity.y()), doSleep), m_physFPS(30) {
    setObjectName("world");
    connect(&m_physTimer, SIGNAL(timeout()), this, SLOT(simStep()));
    m_physTimer.setInterval(round(1000 / m_physFPS));
}

void World::simStep() {
    const float timeStep = 1 / (1000 / round(1000 / m_physFPS)); // the REAL fps is rounded because Qt only supports millisecond precision
    const int velocityIterations = 8;
    const int positionIterations = 1;
    m_world.Step(timeStep, velocityIterations, positionIterations);

    if(!m_selectedObjects.isEmpty()) {
        m_selectedObjects.first()->touch();
    }
}

const QList<Object*>& World::query(const QPointF& point, bool multiSelect) {
    return query(QRectF(point.x()-0.005,point.y()-0.005,0.01,0.01), multiSelect);
}

const QList<Object*>& World::query(const QRectF& rect, bool multiSelect) {
    b2AABB aabb;
    aabb.upperBound = b2Vec2(rect.left(), rect.top());
    aabb.lowerBound = b2Vec2(rect.right(), rect.bottom());
    m_queriedObjects.clear();
    m_multiSelect = multiSelect;
    m_world.QueryAABB(this, aabb);
    return m_queriedObjects;
}

bool World::ReportFixture(b2Fixture* f) {
    // FIXME: ignores multiselect preference, and may report same body twice if clicking between fixtures
    m_queriedObjects.append(static_cast<Object*>(f->GetBody()->GetUserData()));
    return m_multiSelect;
}

QPointF World::gravity() const {
    const b2Vec2& gravity = m_world.GetGravity();
    return QPointF(gravity.x, gravity.y);
}

void World::setGravity(const QPointF& g) {
    if(g != gravity()) {
        m_world.SetGravity(b2Vec2(g.x(), g.y()));
        emit propertyChanged();
    }
}

void World::addObject(Object* obj) {
    m_objects.append(obj);

    b2BodyDef bd;
    obj->m_body = m_world.CreateBody(&bd);
    obj->m_body->SetUserData(obj);

    QList<Polygon> parts = obj->m_poly.ccw().decomp();
    foreach(Polygon poly, parts) {
        QVector<b2Vec2> vertices(poly.size());
        for(int i = 0; i < poly.size(); ++i) {
            vertices[i] = b2Vec2(poly[i].x(), poly[i].y());
        }

        b2PolygonShape ps;
        ps.Set(&vertices[0], vertices.size());

        b2FixtureDef fd;
        fd.density = obj->m_density;
        fd.shape = &ps;

        obj->m_body->CreateFixture(&fd);
    }

    obj->m_body->SetMassFromShapes();

}

const QList<Object*>& World::objects() const {
    return m_objects;
}

const QList<Object*>& World::selectedObjects() const {
    return m_selectedObjects;
}

void World::setSelectedObjects(const QList<Object*>& objs) {
    foreach(Object *obj, m_selectedObjects) {
        obj->m_selected = false;
    }
    m_selectedObjects = objs;
    foreach(Object *obj, objs) {
        obj->m_selected = true;
    }
    emit objectsSelected(objs);
}

void World::setSimulating(bool flag) {
    if(flag != simulating()) {
        if(flag) m_physTimer.start();
        else m_physTimer.stop();
        emit propertyChanged();
    }
}

bool World::simulating() {
    return m_physTimer.isActive();
}