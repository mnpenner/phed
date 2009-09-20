/****************************************************************************
** Meta object code from reading C++ file 'EditorView.h'
**
** Created: Sun Sep 20 14:03:43 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EditorView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditorView[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   37,   11,   11, 0x0a,
      64,   56,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EditorView[] = {
    "EditorView\0\0mousePosChanged(QPointF)\0"
    "tool\0setTool(Tool)\0enabled\0showGrid(bool)\0"
};

const QMetaObject EditorView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_EditorView,
      qt_meta_data_EditorView, 0 }
};

const QMetaObject *EditorView::metaObject() const
{
    return &staticMetaObject;
}

void *EditorView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditorView))
        return static_cast<void*>(const_cast< EditorView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int EditorView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mousePosChanged((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 1: setTool((*reinterpret_cast< Tool(*)>(_a[1]))); break;
        case 2: showGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EditorView::mousePosChanged(const QPointF & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
