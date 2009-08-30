/* 
 * File:   PropertyBrowser.h
 * Author: mark
 *
 * Created on August 23, 2009, 10:29 PM
 */

#ifndef _PROPERTYBROWSER_H
#define	_PROPERTYBROWSER_H

#include <QtPropertyBrowser/QtTreePropertyBrowser>
#include <QtPropertyBrowser/QtVariantPropertyManager>

class PropertyBrowser : public QtTreePropertyBrowser {
    Q_OBJECT
public:
    PropertyBrowser(QWidget *parent = NULL);
    void setSelectedObjects(QList<QObject*> objs);

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);
    void objectUpdated();

private:
    QString humanize(QString str) const;
    QtVariantPropertyManager *m_variantManager;
    QMap<QtProperty*, QByteArray> m_propertyMap;
    QList<QObject*> m_selectedObjects;
};

#endif	/* _PROPERTYBROWSER_H */

