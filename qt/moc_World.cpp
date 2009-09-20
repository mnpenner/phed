/****************************************************************************
** Meta object code from reading C++ file 'World.h'
**
** Created: Sun Sep 20 14:04:31 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../World.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'World.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_World[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       1,   27, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,
      25,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,    6,    6,    6, 0x09,

 // properties: name, type, flags
      76,   68, 0x1a095103,

       0        // eod
};

static const char qt_meta_stringdata_World[] = {
    "World\0\0propertyChanged()\0"
    "objectsSelected(QList<QObject*>)\0"
    "simStep()\0QPointF\0gravity\0"
};

const QMetaObject World::staticMetaObject = {
    { &Object::staticMetaObject, qt_meta_stringdata_World,
      qt_meta_data_World, 0 }
};

const QMetaObject *World::metaObject() const
{
    return &staticMetaObject;
}

void *World::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_World))
        return static_cast<void*>(const_cast< World*>(this));
    if (!strcmp(_clname, "b2QueryCallback"))
        return static_cast< b2QueryCallback*>(const_cast< World*>(this));
    if (!strcmp(_clname, "b2ContactListener"))
        return static_cast< b2ContactListener*>(const_cast< World*>(this));
    return Object::qt_metacast(_clname);
}

int World::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: propertyChanged(); break;
        case 1: objectsSelected((*reinterpret_cast< const QList<QObject*>(*)>(_a[1]))); break;
        case 2: simStep(); break;
        default: ;
        }
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPointF*>(_v) = gravity(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setGravity(*reinterpret_cast< QPointF*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void World::propertyChanged()const
{
    QMetaObject::activate(const_cast< World *>(this), &staticMetaObject, 0, 0);
}

// SIGNAL 1
void World::objectsSelected(const QList<QObject*> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
