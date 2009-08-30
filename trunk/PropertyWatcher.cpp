/* 
 * File:   PropertyWatcher.cpp
 * Author: mark
 * 
 * Created on August 23, 2009, 11:17 AM
 */

#include <QtCore/QRegExp>
#include <qt4/QtPropertyBrowser/qttreepropertybrowser.h>
#include "PropertyWatcher.h"

PropertyWatcher::PropertyWatcher(QObject *parent)
: QObject(parent), m_variantManager(new QtVariantPropertyManager(this)),
m_selectedObj(NULL) {
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty*, QVariant)),
            SLOT(valueChanged(QtProperty*, QVariant)));
    addProperties();
}

QString PropertyWatcher::humanize(QString str) const {
    return str.at(0).toUpper() + str.mid(1).replace(QRegExp("([a-z])([A-Z])"), "\\1 \\2");
}

void PropertyWatcher::addProperties() {
    Object obj;
    m_propGroup = m_variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), obj.metaObject()->className());
    
    int numProperties = obj.metaObject()->propertyCount();
    for(int i = 0; i < numProperties; ++i) {
        QMetaProperty metaProperty(obj.metaObject()->property(i));
        QtProperty * const property
                = m_variantManager->addProperty(metaProperty.type(), humanize(metaProperty.name()));
        property->setEnabled(metaProperty.isWritable());
        m_propGroup->addSubProperty(property);
        m_propertyMap[property] = metaProperty.name();
    }
}

void PropertyWatcher::setSelectedObject(Object *obj) {
    if(m_selectedObj) {
        m_selectedObj->disconnect(this);
    }
    m_selectedObj = obj;
    if(obj) {
        connect(obj, SIGNAL(propertyChanged()), SLOT(objectUpdated()));
        objectUpdated();
    }
}

QtVariantPropertyManager* PropertyWatcher::propertyManager() {
    return m_variantManager;
}

void PropertyWatcher::setBrowser(QtAbstractPropertyBrowser *browser) {
    browser->setFactoryForManager(m_variantManager, new QtVariantEditorFactory);
    browser->addProperty(m_propGroup);
}

void PropertyWatcher::valueChanged(QtProperty *property, const QVariant &value) {
    if(m_selectedObj && m_propertyMap.find(property) != m_propertyMap.end()) {
        m_selectedObj->setProperty(m_propertyMap[property], value);
    }
}

void PropertyWatcher::objectUpdated() {
    m_variantManager->disconnect(this);
    QMapIterator<QtProperty*, QByteArray> i(m_propertyMap);
    while(i.hasNext()) {
        i.next();
        m_variantManager->setValue(i.key(), m_selectedObj->property(i.value()));
    }
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty*, QVariant)),
            SLOT(valueChanged(QtProperty*, QVariant)));
}

