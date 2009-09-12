TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = Phed
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui opengl
SOURCES += EditorView.cpp Browsable.cpp PropertyBrowser.cpp Polygon.cpp main.cpp Object.cpp EditorWindow.cpp World.cpp Point.cpp
HEADERS += Object.h World.h PropertyBrowser.h Browsable.h Polygon.h EditorView.h EditorWindow.h Point.h
FORMS +=
RESOURCES += icons.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = qt
RCC_DIR = qt
UI_DIR = qt
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/qt4 
LIBS += -lBox2D -lQtSolutions_PropertyBrowser-2.5  -Wl,-rpath /usr/local/lib 
