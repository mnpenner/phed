/* 
 * File:   PropertiesWindow.cpp
 * Author: mark
 * 
 * Created on August 17, 2009, 12:17 PM
 */

#include <QtPropertyBrowser/qtpropertybrowser.h>
#include <QtPropertyBrowser/qtvariantproperty.h>
#include <QtPropertyBrowser/qttreepropertybrowser.h>
#include "PropertiesWindow.h"

PropertiesWindow::PropertiesWindow(QWidget *parent)
: QDockWidget(parent), m_propertyBrowser(new PropertyBrowser) {
    setWindowTitle("Properties");
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_propertyBrowser = new PropertyBrowser;
    setWidget(m_propertyBrowser);
}

void PropertiesWindow::populate(const QList<QObject*> &objs) {
    m_propertyBrowser->setSelectedObjects(objs);
}
