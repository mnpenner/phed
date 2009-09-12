/* 
 * File:   World.cpp
 * Author: mark
 * 
 * Created on August 31, 2009, 6:32 PM
 */

#include "World.h"
#include "Object.h"

World::World(const QPointF& gravity, bool doSleep, QObject *parent)
: QObject(parent), m_world(b2Vec2(gravity.x(), gravity.y()), doSleep), m_physFPS(60) {
    setObjectName("world");
    connect(&m_physTimer, SIGNAL(timeout()), this, SLOT(simStep()));
    m_physTimer.setInterval(round(1000 / m_physFPS));
}

void World::simStep() {
    const float timeStep = 1 / (1000 / round(1000 / m_physFPS)); // the REAL fps is rounded because Qt only supports millisecond precision
    const int velocityIterations = 8;
    const int positionIterations = 3;
    m_world.Step(timeStep, velocityIterations, positionIterations);

    if(!m_selectedObjects.isEmpty()) {
        if(m_selectedObjects.first()->inherits("Object")) {
            static_cast<Object*>(m_selectedObjects.first())->touch();
        }
    }
}

const QSet<Object*>& World::query(const QPointF& point, int limit) {
    return query(QRectF(point.x()-0.005,point.y()-0.005,0.01,0.01), limit);
}

const QSet<Object*>& World::query(const QRectF& rect, int limit) {
    b2AABB aabb;
    aabb.upperBound = b2Vec2(rect.left(), rect.top());
    aabb.lowerBound = b2Vec2(rect.right(), rect.bottom());
    m_queryResult.clear();
    m_queryResultsLimit = limit;
    m_queryPoly.SetAsBox(aabb.GetExtents().x, aabb.GetExtents().y, aabb.GetCenter(), 0);
    m_world.QueryAABB(this, aabb);
    return m_queryResult;
}

bool World::ReportFixture(b2Fixture* f) {
    if(m_queryResultsLimit != 0 && m_queryResult.size() >= m_queryResultsLimit) {
        return false;
    }
    b2Manifold manifold;
    b2Transform trans;
    trans.SetIdentity();
    b2CollidePolygons(&manifold, static_cast<b2PolygonShape*>(f->GetShape()),
            f->GetBody()->GetTransform(), &m_queryPoly, trans);
    if(manifold.m_pointCount > 0) {
        m_queryResult.insert(static_cast<Object*>(f->GetBody()->GetUserData()));
    }
    return true;
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

const QList<QObject*>& World::selectedObjects() const {
    return m_selectedObjects;
}

void World::setSelectedObjects(const QSet<Object*>& objs) {
    QList<QObject*> qobjs;
    foreach(QObject *obj, m_selectedObjects) {
        obj->setProperty("selected", false);
    }
    if(objs.isEmpty()) {
        qobjs.append(this);
    } else {
        foreach(Object *obj, objs) {
            obj->setProperty("selected", true);
            qobjs.append(obj);
        }
    }
    m_selectedObjects = qobjs;
    emit objectsSelected(qobjs);
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