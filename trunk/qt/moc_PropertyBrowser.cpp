/****************************************************************************
** Meta object code from reading C++ file 'PropertyBrowser.h'
**
** Created: Sun Sep 20 14:03:34 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PropertyBrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PropertyBrowser[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      32,   17,   16,   16, 0x08,
      67,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PropertyBrowser[] = {
    "PropertyBrowser\0\0property,value\0"
    "valueChanged(QtProperty*,QVariant)\0"
    "objectUpdated()\0"
};

const QMetaObject PropertyBrowser::staticMetaObject = {
    { &QtTreePropertyBrowser::staticMetaObject, qt_meta_stringdata_PropertyBrowser,
      qt_meta_data_PropertyBrowser, 0 }
};

const QMetaObject *PropertyBrowser::metaObject() const
{
    return &staticMetaObject;
}

void *PropertyBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PropertyBrowser))
        return static_cast<void*>(const_cast< PropertyBrowser*>(this));
    return QtTreePropertyBrowser::qt_metacast(_clname);
}

int PropertyBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtTreePropertyBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 1: objectUpdated(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
