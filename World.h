/* 
 * File:   World.h
 * Author: mark
 *
 * Created on August 31, 2009, 6:32 PM
 */

#ifndef _WORLD_H
#define	_WORLD_H

#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QSet>
#include <Box2D/Box2D.h>
#include "Point.h"
#include "Polygon.h"
#include "Rect.h"
#include "Object.h"

class Body;

struct Contact {
    Point lp; // local point
    Point wp; // world point
    Point n; // normal
    b2Fixture *f; // fixture
    qreal I; // impulse magnitude
    Point lv; // linear velocity
    qreal av; // angular velocity
};

class World : public Object, b2QueryCallback, b2ContactListener {
    Q_OBJECT
    Q_PROPERTY(QPointF gravity  READ gravity    WRITE setGravity);
    
public:
    World(const QPointF &gravity = QPointF(0, -9.80665), bool doSleep = true, QObject *parent = NULL);

    // read
    QPointF gravity() const;
    bool simulating();
    b2MouseJoint *mouseJoint();

    // write
    void setGravity(const QPointF&);
    void setSimulating(bool);

    // misc
    void addBody(Body*);
    void removeObject(Body*);
    const QList<Body*>& bodies() const;
    const QList<Object*>& selectedObjects() const;
    void setSelectedObjects(const QSet<Body*>&);
    const QSet<Body*>& query(const Point& point, int maxResults = 1);
    const QSet<Body*>& query(const Polygon& rect, int maxResults = 0);
    b2Body* groundBody() const;

    void addMouseJoint(Body*, const Point &p); // FIXME: should be a list of bodies, or abstracted to general joint
    void destroyMouseJoint();
    void updateMouseJoint(const Point &p);

    void reset();


protected:
    bool ReportFixture(b2Fixture *f);
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse);

signals:
    void propertyChanged() const;
    void objectsSelected(const QList<Object*>&);

protected slots:
    void simStep();

private:
    b2World m_world;
    b2Body *m_groundBody;
    QList<Body*> m_bodies;
    QList<Object*> m_selectedObjects;
    QSet<Body*> m_queryResult;
    QTimer m_physTimer;
    int m_physFPS;
    int m_queryResultsLimit;
    Polygon m_queryPoly;
    b2MouseJoint *m_mouseJoint;
    
    int m_manifoldPointCount;
    b2Fixture *m_fixtureA;
    b2Fixture *m_fixtureB;
    Body *m_objA;
    Body *m_objB;
    QList<Contact> m_contacts;
    b2Vec2 m_lv1, m_lv2;
    qreal m_av1, m_av2;
};

#endif	/* _WORLD_H */

