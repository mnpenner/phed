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
    const QList<Object*>& selectedObjects() const;
    void setSelectedObjects(const QList<Object*>&);
    const QList<Object*>& query(const QPointF& point, bool multiSelect = false);
    const QList<Object*>& query(const QRectF& rect, bool multiSelect = true);


protected:
    bool ReportFixture(b2Fixture *f);

signals:
    void propertyChanged() const;
    void objectsSelected(const QList<Object*>&);

protected slots:
    void simStep();

private:
    b2World m_world;
    QList<Object*> m_objects;
    QList<Object*> m_selectedObjects;
    QList<Object*> m_queriedObjects;
    QTimer m_physTimer;
    int m_physFPS;
    bool m_multiSelect;
};

#endif	/* _WORLD_H */

