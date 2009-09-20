/* 
 * File:   Object.cpp
 * Author: mark
 * 
 * Created on September 20, 2009, 1:56 PM
 */

#include <QtCore/QMetaProperty>
#include "Object.h"

Object::Object(QObject* parent) : QObject(parent) {}

void Object::touch() const {
    emit propertyChanged();
}

QDataStream &operator<<(QDataStream &ds, const Object &obj) {
    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
        if(obj.metaObject()->property(i).isStored(&obj)) {
            Q_ASSERT(obj.metaObject()->property(i).isReadable());
            ds << obj.metaObject()->property(i).read(&obj);
        }
    }
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Object &obj) {
    QVariant var;
    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
        if(obj.metaObject()->property(i).isStored(&obj)) {
            Q_ASSERT(obj.metaObject()->property(i).isWritable());
            ds >> var;
            obj.metaObject()->property(i).write(&obj, var);
        }
    }
    return ds;
}