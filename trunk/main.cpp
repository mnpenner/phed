/*
 * File:   main.cpp
 * Author: mark
 *
 * Created on August 9, 2009, 5:51 PM
 */

#include <QtGui/QApplication>
#include <QtOpenGL>
#include "LauncherDialog.h"
#include "EditorWindow.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("mnbGames");
    QCoreApplication::setOrganizationDomain("mnbayazit.com");
    QCoreApplication::setApplicationName("Q2D");

    //QGLFormat fmt = QGLFormat::defaultFormat();
    //fmt.setSampleBuffers(true);
    //QGLFormat::setDefaultFormat(fmt);

    QApplication app(argc, argv);
    
    //LauncherDialog mainMenu;
    ///mainMenu.show();

    EditorWindow ed;
    ed.show();

    return app.exec();
}
