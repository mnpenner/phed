/* 
 * File:   PropertyWatcher.h
 * Author: mark
 *
 * Created on August 23, 2009, 11:17 AM
 */

#ifndef _PROPERTYWATCHER_H
#define	_PROPERTYWATCHER_H

#include <QtCore>
#include <QtPropertyBrowser/QtVariantPropertyManager>
#include "Object.h"

class PropertyWatcher : public QObject {

    Q_OBJECT
public:
    PropertyWatcher(QObject *parent = NULL);
    void addProperties();
    void setSelectedObject(Object *obj);
    QtVariantPropertyManager* propertyManager();
    void setBrowser(QtAbstractPropertyBrowser *browser);

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);
    void objectUpdated();

public:
    QString humanize(QString str) const;
    QtVariantPropertyManager *const m_variantManager;
    QMap<QtProperty*, QByteArray> m_propertyMap;
    QPointer<Object> m_selectedObj;
    QtProperty *m_propGroup;
};

#endif	/* _PROPERTYWATCHER_H */

