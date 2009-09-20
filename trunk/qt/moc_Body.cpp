/****************************************************************************
** Meta object code from reading C++ file 'Body.h'
**
** Created: Sun Sep 20 14:19:22 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Body.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Body.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Body[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      19,   12, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      11,    5, 0x06085001,
      16,    5, 0x06085001,
      29,   24, 0x01085001,
      38,   24, 0x01085001,
      58,   50, 0x1a095103,
      67,   50, 0x1a095103,
      82,    5, 0x06095103,
      88,    5, 0x06095103,
     104,    5, 0x06095103,
     118,    5, 0x06095103,
     133,    5, 0x06095103,
     141,    5, 0x06095103,
     150,    5, 0x06095103,
     162,    5, 0x06095103,
     176,   24, 0x01095003,
     185,   24, 0x01095003,
     202,   24, 0x01095003,
     213,   24, 0x01095003,
     229,  222, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_Body[] = {
    "Body\0qreal\0mass\0inertia\0bool\0isStatic\0"
    "isBreakable\0QPointF\0position\0"
    "linearVelocity\0angle\0angularVelocity\0"
    "linearDamping\0angularDamping\0density\0"
    "friction\0restitution\0breakingPoint\0"
    "isBullet\0isAllowedToSleep\0isSleeping\0"
    "isSensor\0QColor\0color\0"
};

const QMetaObject Body::staticMetaObject = {
    { &Object::staticMetaObject, qt_meta_stringdata_Body,
      qt_meta_data_Body, 0 }
};

const QMetaObject *Body::metaObject() const
{
    return &staticMetaObject;
}

void *Body::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Body))
        return static_cast<void*>(const_cast< Body*>(this));
    return Object::qt_metacast(_clname);
}

int Body::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = mass(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = inertia(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isStatic(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isBreakable(); break;
        case 4: *reinterpret_cast< QPointF*>(_v) = position(); break;
        case 5: *reinterpret_cast< QPointF*>(_v) = linearVelocity(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = angle(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = angularVelocity(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = linearDamping(); break;
        case 9: *reinterpret_cast< qreal*>(_v) = angularDamping(); break;
        case 10: *reinterpret_cast< qreal*>(_v) = density(); break;
        case 11: *reinterpret_cast< qreal*>(_v) = friction(); break;
        case 12: *reinterpret_cast< qreal*>(_v) = restitution(); break;
        case 13: *reinterpret_cast< qreal*>(_v) = breakingPoint(); break;
        case 14: *reinterpret_cast< bool*>(_v) = isBullet(); break;
        case 15: *reinterpret_cast< bool*>(_v) = isAllowedToSleep(); break;
        case 16: *reinterpret_cast< bool*>(_v) = isSleeping(); break;
        case 17: *reinterpret_cast< bool*>(_v) = isSensor(); break;
        case 18: *reinterpret_cast< QColor*>(_v) = color(); break;
        }
        _id -= 19;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: setPosition(*reinterpret_cast< QPointF*>(_v)); break;
        case 5: setLinearVelocity(*reinterpret_cast< QPointF*>(_v)); break;
        case 6: setAngle(*reinterpret_cast< qreal*>(_v)); break;
        case 7: setAngularVelocity(*reinterpret_cast< qreal*>(_v)); break;
        case 8: setLinearDamping(*reinterpret_cast< qreal*>(_v)); break;
        case 9: setAngularDamping(*reinterpret_cast< qreal*>(_v)); break;
        case 10: setDensity(*reinterpret_cast< qreal*>(_v)); break;
        case 11: setFriction(*reinterpret_cast< qreal*>(_v)); break;
        case 12: setRestitution(*reinterpret_cast< qreal*>(_v)); break;
        case 13: setBreakingPoint(*reinterpret_cast< qreal*>(_v)); break;
        case 14: setBullet(*reinterpret_cast< bool*>(_v)); break;
        case 15: setAllowedToSleep(*reinterpret_cast< bool*>(_v)); break;
        case 16: setSleeping(*reinterpret_cast< bool*>(_v)); break;
        case 17: setSensor(*reinterpret_cast< bool*>(_v)); break;
        case 18: setColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 19;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 19;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
