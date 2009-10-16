/*
 * File:   main.cpp
 * Author: mark
 *
 * Created on August 9, 2009, 5:51 PM
 */
#include <QtGui/QApplication>
#include "EditorWindow.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon.h"
#include "Point.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("mnbGames");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/phed/");
    QCoreApplication::setApplicationName("Phed");
    
    qsrand(QDateTime::currentDateTime().toTime_t());

    QApplication app(argc, argv);

    qRegisterMetaType<Rect>("Rect");
    qRegisterMetaType<Circle>("Circle");
    qRegisterMetaType<Polygon>("Polygon");
    qRegisterMetaType<Point>("Point");
    qRegisterMetaType<PolygonList>("PolygonList");
    qRegisterMetaTypeStreamOperators<PolygonList>("PolygonList");
    
    EditorWindow ew;
    ew.show();

    return app.exec();
}
