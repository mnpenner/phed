/* 
 * File:   PropertiesWindow.h
 * Author: mark
 *
 * Created on August 17, 2009, 12:17 PM
 */

#ifndef _PROPERTIESWINDOW_H
#define	_PROPERTIESWINDOW_H

#include <QtGui>
#include "Object.h"
#include "PropertyBrowser.h"

class PropertiesWindow : public QDockWidget {
    Q_OBJECT
public:
    PropertiesWindow(QWidget *parent = NULL);

public slots:
    void populate(const QList<QObject*> &objs);

private:
    PropertyBrowser *m_propertyBrowser;
};

#endif	/* _PROPERTIESWINDOW_H */

