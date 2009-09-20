/****************************************************************************
** Meta object code from reading C++ file 'EditorWindow.h'
**
** Created: Sun Sep 20 14:03:40 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EditorWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditorWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      24,   13,   13,   13, 0x08,
      36,   13,   31,   13, 0x08,
      43,   13,   31,   13, 0x08,
      52,   13,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      77,   13,   13,   13, 0x08,
     100,   13,   13,   13, 0x08,
     117,   13,   13,   13, 0x08,
     142,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditorWindow[] = {
    "EditorWindow\0\0newFile()\0open()\0bool\0"
    "save()\0saveAs()\0about()\0mapWasModified()\0"
    "toolSelected(QAction*)\0toggleSimState()\0"
    "mousePosChanged(QPointF)\0"
    "objectsSelected(QList<QObject*>)\0"
};

const QMetaObject EditorWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditorWindow,
      qt_meta_data_EditorWindow, 0 }
};

const QMetaObject *EditorWindow::metaObject() const
{
    return &staticMetaObject;
}

void *EditorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditorWindow))
        return static_cast<void*>(const_cast< EditorWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: open(); break;
        case 2: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: about(); break;
        case 5: mapWasModified(); break;
        case 6: toolSelected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: toggleSimState(); break;
        case 8: mousePosChanged((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 9: objectsSelected((*reinterpret_cast< const QList<QObject*>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
