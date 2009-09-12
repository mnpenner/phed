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

class Object;

class World : public QObject, b2QueryCallback {
    Q_OBJECT
    Q_PROPERTY(QPointF gravity  READ gravity    WRITE setGravity);
    
public:
    World(const QPointF &gravity = QPointF(0, -9.80665), bool doSleep = true, QObject *parent = NULL);

    // read
    QPointF gravity() const;
    bool simulating();

    // write
    void setGravity(const QPointF&);
    void setSimulating(bool);

    // misc
    void addObject(Object*);
    const QList<Object*>& objects() const;
    const QList<QObject*>& selectedObjects() const;
    void setSelectedObjects(const QSet<Object*>&);
    const QSet<Object*>& query(const QPointF& point, int maxResults = 1);
    const QSet<Object*>& query(const QRectF& rect, int maxResults = 0);


protected:
    bool ReportFixture(b2Fixture *f);

signals:
    void propertyChanged() const;
    void objectsSelected(const QList<QObject*>&);

protected slots:
    void simStep();

private:
    b2World m_world;
    QList<Object*> m_objects;
    QList<QObject*> m_selectedObjects;
    QSet<Object*> m_queryResult;
    QTimer m_physTimer;
    int m_physFPS;
    int m_queryResultsLimit;
    b2PolygonShape m_queryPoly;
};

#endif	/* _WORLD_H */

