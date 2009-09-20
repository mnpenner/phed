/* 
 * File:   World.cpp
 * Author: mark
 * 
 * Created on August 31, 2009, 6:32 PM
 */

#include "World.h"
#include "Body.h"
#include "ScopedPointer.h"

World::World(const QPointF& gravity, bool doSleep, QObject *parent)
: QObject(parent), m_world(b2Vec2(gravity.x(), gravity.y()), doSleep), m_physFPS(60), m_mouseJoint(NULL) {
    setObjectName("world");
    connect(&m_physTimer, SIGNAL(timeout()), this, SLOT(simStep()));
    m_physTimer.setInterval(round(1000 / m_physFPS));
    m_groundBody = m_world.CreateBody(ScopedPointer<b2BodyDef > ());
    m_world.SetContactListener(this);
}

void World::BeginContact(b2Contact*) {
}

void World::EndContact(b2Contact*) {

}

void World::PreSolve(b2Contact* contact, const b2Manifold*) {
    m_manifoldPointCount = contact->GetManifold()->m_pointCount;
    m_fixtureA = contact->GetFixtureA();
    m_fixtureB = contact->GetFixtureB();
    m_objA = static_cast<Body*>(contact->GetFixtureA()->GetBody()->GetUserData());
    m_objB = static_cast<Body*>(contact->GetFixtureB()->GetBody()->GetUserData());
    m_lv1 = m_objA->body()->GetLinearVelocity();
    m_av1 = m_objA->body()->GetAngularVelocity();
    m_lv2 = m_objB->body()->GetLinearVelocity();
    m_av2 = m_objB->body()->GetAngularVelocity();
}

void World::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse) {
    b2WorldManifold wm;
    contact->GetWorldManifold(&wm);
    for(int i = 0; i < contact->GetManifold()->m_pointCount; ++i) {
        Contact c;
        c.n = contact->GetManifold()->m_localPlaneNormal;
        c.I = impulse->normalImpulses[i];
        c.lp = contact->GetManifold()->m_points[i].m_localPoint;
        c.wp = wm.m_points[i];
        if(m_objA->isBreakable() && c.I > m_objA->breakingPoint()) {
            c.f = m_fixtureA;
            c.lv = (Point)m_lv1;
            c.av = (qreal)m_av1;
            m_contacts.append(c);
        }
        if(m_objB->isBreakable() && c.I > m_objB->breakingPoint()) {
            c.f = m_fixtureB;
            c.lv = m_lv2;
            c.av = m_av2;
            m_contacts.append(c);
        }
    }
}

b2Body* World::groundBody() const {
    return m_groundBody;
}

void World::simStep() {
    // explode some fixtures
    foreach(Contact c, m_contacts) {
        Polygon fixture = *static_cast<b2PolygonShape*>(c.f->GetShape());
        Polygon blast = Circle(c.lp, 0.5);
        Polygon intersec = fixture.intersected(blast);
        Polygon rest = fixture.subtracted(blast);

        Body *obj;
        Body *orig = static_cast<Body*>(c.f->GetBody()->GetUserData());

        qreal I = sqrt(c.I)/10;
        b2Vec2 impulse = b2Vec2(I*c.n.x(), I*c.n.y());

        if(!intersec.isEmpty()) {
            obj = new Body(intersec, this);
            addBody(obj);
            obj->setPosition(c.f->GetBody()->GetPosition());
            obj->setAngle(c.f->GetBody()->GetAngle());
            obj->setColor(orig->color());
            obj->setBreakingPoint(orig->breakingPoint());
            obj->setLinearVelocity(c.lv);
            obj->setAngularVelocity(c.av);
        }
        
        if(!rest.isEmpty()) {
            obj = new Body(rest, this);
            addBody(obj);
            obj->setPosition(c.f->GetBody()->GetPosition());
            obj->setAngle(c.f->GetBody()->GetAngle());
            obj->setColor(orig->color());
            obj->setBreakingPoint(orig->breakingPoint());
            obj->setLinearVelocity(c.lv);
            obj->setAngularVelocity(c.av);
        }
       
        c.f->GetBody()->DestroyFixture(c.f);
        break; // fixture is no longer valid so we can only do 1 per loop...
    }
    m_contacts.clear();


    // advance the physics simulation
    const float timeStep = 1 / (1000 / round(1000 / m_physFPS)); // the REAL fps is rounded because Qt only supports millisecond precision
    const int velocityIterations = 8;
    const int positionIterations = 3;
    m_world.Step(timeStep, velocityIterations, positionIterations);

    if(!m_selectedObjects.isEmpty()) {
        if(m_selectedObjects.first()->inherits("Body")) {
            static_cast<Body*> (m_selectedObjects.first())->touch();
        }
    }
}

const QSet<Body*>& World::query(const Point& point, int limit) {
    return query(Rect(point.x() - 0.005, point.y() - 0.005, 0.01, 0.01), limit);
}

const QSet<Body*>& World::query(const Polygon& poly, int limit) {
    m_queryResult.clear();
    m_queryResultsLimit = limit;
    m_queryPoly = poly;
    m_world.QueryAABB(this, (Rect)poly.boundingRect());
    return m_queryResult;
}

bool World::ReportFixture(b2Fixture* f) {
    if(m_queryResultsLimit > 0 && m_queryResult.size() >= m_queryResultsLimit) {
        return false;
    }
    b2Manifold manifold;
    b2Transform trans;
    trans.SetIdentity();
    b2CollidePolygons(&manifold, static_cast<b2PolygonShape*> (f->GetShape()),
            f->GetBody()->GetTransform(), &static_cast<b2PolygonShape>(m_queryPoly), trans);
    if(manifold.m_pointCount > 0) {
        m_queryResult.insert(static_cast<Body*> (f->GetBody()->GetUserData()));
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

void World::addBody(Body* obj) {
    int fixtureCount = 0;
    obj->m_body = m_world.CreateBody(&obj->m_bodyDef);
    
    QList<Polygon> parts = obj->m_poly.ccw().decomp();

    foreach(Polygon poly, parts) {
        for(int i=0; i<poly.size(); ++i) {
            Point edge = poly[i] - poly.at(i+1);
            if(edge.lengthSquared() <= B2_FLT_EPSILON * B2_FLT_EPSILON) {
                poly.remove(i);
            }
        }
        if(poly.size() < 3) continue;
        if(poly.area() <= B2_FLT_EPSILON) continue;

        QVector<b2Vec2> vertices(poly.size());
        for(int i = 0; i < poly.size(); ++i) {
            vertices[i] = (Point) poly[i];
        }

        b2PolygonShape ps;
        ps.Set(&vertices[0], vertices.size());

        obj->m_fixtureDef.shape = &ps;
        obj->m_body->CreateFixture(&obj->m_fixtureDef);
        
        fixtureCount++;
    }

    if(fixtureCount <= 0) {
        m_world.DestroyBody(obj->body());
        return;
    }

    obj->m_body->SetMassFromShapes();
    obj->m_body->SetUserData(obj);
    m_objects.append(obj);
}

void World::removeObject(Body* obj) { // FIXME: causes crashes (or leaks without deleting the obj??)
    m_world.DestroyBody(obj->body());
    m_objects.removeOne(obj);
    m_selectedObjects.removeOne(obj);
    //obj->deleteLater();
}

b2MouseJoint *World::mouseJoint() {
    return m_mouseJoint;
}

void World::addMouseJoint(Body* obj, const Point &p) {
    destroyMouseJoint();
    b2MouseJointDef md;
    md.body1 = m_groundBody;
    md.body2 = obj->body();
    md.target = p;
    md.maxForce = obj->mass() * 1000;
    m_mouseJoint = static_cast<b2MouseJoint*> (m_world.CreateJoint(&md));
    obj->setSleeping(false);
}

void World::updateMouseJoint(const Point& p) {
    Q_ASSERT(m_mouseJoint != NULL);
    m_mouseJoint->SetTarget(p);
}

void World::destroyMouseJoint() {
    if(m_mouseJoint != NULL) {
        m_world.DestroyJoint(m_mouseJoint);
        m_mouseJoint = NULL;
    }
}

const QList<Body*>& World::objects() const {
    return m_objects;
}

const QList<QObject*>& World::selectedObjects() const {
    return m_selectedObjects;
}

void World::setSelectedObjects(const QSet<Body*>& objs) {
    QList<QObject*> qobjs;

    foreach(QObject *obj, m_selectedObjects) {
        obj->setProperty("selected", false);
    }
    if(objs.isEmpty()) {
        qobjs.append(this);
    } else {

        foreach(Body *obj, objs) {
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