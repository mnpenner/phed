/* 
 * File:   PropertyBrowser.cpp
 * Author: mark
 * 
 * Created on August 23, 2009, 10:29 PM
 */

#include <QtCore/QMetaProperty>
#include <qt4/QtCore/qdatetime.h>
#include "PropertyBrowser.h"
#include "Object.h"

PropertyBrowser::PropertyBrowser(QWidget* parent)
: QtTreePropertyBrowser(parent), m_variantManager(new QtVariantPropertyManager(this)), m_variantEditorFactory(new QtVariantEditorFactory(this)) {
    setHeaderVisible(false);
    setPropertiesWithoutValueMarked(true);
    setIndentation(10);
    setResizeMode(ResizeToContents);
    setAlternatingRowColors(false);
    setFactoryForManager(m_variantManager, new QtVariantEditorFactory);
    
}

void PropertyBrowser::valueChanged(QtProperty *property, const QVariant &value) {
    if(m_propertyMap.find(property) != m_propertyMap.end()) { 
        foreach(QObject *obj, m_selectedObjects) {
            obj->setProperty(m_propertyMap[property], value);
        }
    }
}

QString PropertyBrowser::humanize(QString str) const {
    return str.at(0).toUpper() + str.mid(1).replace(QRegExp("([a-z])([A-Z])"), "\\1 \\2");
}

void PropertyBrowser::setSelectedObjects(const QList<QObject*>& objs) {
    foreach(QObject *obj, m_selectedObjects) {
        disconnect(obj, SIGNAL(propertyChanged()), this, SLOT(objectUpdated()));
    }
    
    clear();
    m_selectedObjects = objs;

    const QMetaObject *metaObject = objs.first()->metaObject();
    const QByteArray className = metaObject->className();

    QTime timer;
    timer.start();
    if(m_classManager.find(className) == m_classManager.end()) { // manager does not exist
        m_classManager[className] = new QtVariantPropertyManager(this);
        setFactoryForManager(m_classManager[className], m_variantEditorFactory);
        for(int i=0; i< metaObject->propertyCount(); ++i) {
            QMetaProperty metaProperty(metaObject->property(i));
            QtProperty *property = m_classManager[className]->addProperty(metaProperty.type(), metaProperty.name());
            m_classProperties[className][metaProperty.name()] = property;
            addProperty(property);
            setExpanded(topLevelItem(property), false);
        }
    } else {
        QHashIterator<QByteArray, QtProperty*> i(m_classProperties[className]);
        while(i.hasNext()) {
            i.next();
            addProperty(i.value());
            setExpanded(topLevelItem(i.value()), false);
        }
    }
    printf("%d ms\n", timer.elapsed());
    foreach(QObject *obj, m_selectedObjects) {
        connect(obj, SIGNAL(propertyChanged()), this, SLOT(objectUpdated()));
    }
    objectUpdated();
}
/*
void PropertyBrowser::setSelectedObjects(const QList<QObject*> &objs) {
    foreach(QObject *obj, m_selectedObjects) {
        disconnect(obj, SIGNAL(propertyChanged()), this, SLOT(objectUpdated()));
    }
    clear();
    m_variantManager->clear();
    m_selectedObjects = objs;
    m_propertyMap.clear();
    if(objs.isEmpty()) {
        return;
    }
    for(int i = 0; i < objs.first()->metaObject()->propertyCount(); ++i) { // FIXME: this loop takes ~250 ms for 18 properties
        QMetaProperty metaProperty(objs.first()->metaObject()->property(i));
        QtProperty * const property
                = m_variantManager->addProperty(metaProperty.type(), humanize(metaProperty.name()));
        property->setEnabled(metaProperty.isWritable());
        m_propertyMap[property] = metaProperty.name();
        addProperty(property);
        setExpanded(topLevelItem(property), false);
    }
    foreach(QObject *obj, m_selectedObjects) {
        connect(obj, SIGNAL(propertyChanged()), this, SLOT(objectUpdated()));
    }
    objectUpdated();
    
}
*/
void PropertyBrowser::objectUpdated() {
    if(m_selectedObjects.isEmpty()) {
        return;
    }
    disconnect(m_variantManager, SIGNAL(valueChanged(QtProperty*, QVariant)), 
            this, SLOT(valueChanged(QtProperty*, QVariant)));
    QMapIterator<QtProperty*, QByteArray> i(m_propertyMap); // FIXME: should be looping over object's properties, not property map
    bool diff;
    while(i.hasNext()) {
        i.next();
        diff = false;
        for(int j = 1; j < m_selectedObjects.size(); ++j) {
            if(m_selectedObjects.at(j)->property(i.value()) != m_selectedObjects.at(j - 1)->property(i.value())) {
                diff = true;
                break;
            }
        }
        if(diff) setBackgroundColor(topLevelItem(i.key()), QColor(0xFF,0xFE,0xA9));
        else setBackgroundColor(topLevelItem(i.key()), Qt::white);
        m_variantManager->setValue(i.key(), m_selectedObjects.first()->property(i.value()));
    }
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty*, QVariant)), 
            this, SLOT(valueChanged(QtProperty*, QVariant)));
}