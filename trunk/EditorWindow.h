/* 
 * File:   EditorWindow.h
 * Author: mark
 *
 * Created on August 11, 2009, 11:20 AM
 */

#ifndef _EDITORWINDOW_H
#define	_EDITORWINDOW_H

#include <QtGui>
#include "EditorScene.h"
#include "PropertyBrowser.h"

class EditorView;
class PropertiesWindow;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void mapWasModified();
    void mousePosChanged(QPointF);
    void toolSelected(QAction*);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void writeSettings();
    void readSettings();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *controlMenu;
    QMenu *windowsMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *toolsToolBar;
    QToolBar *controlToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *showGridAct;
    QAction *snapToGridAct;

    QActionGroup *controlActGroup;
    QAction *playAct;
    QAction *pauseAct;
    QAction *stopAct;

    QActionGroup *toolsActGroup;
    QAction *selectToolAct;
    QAction *circleToolAct;
    QAction *polygonToolAct;
    QAction *rectToolAct;
    QAction *lineToolAct;

    EditorScene *m_scene;
    QGraphicsView *m_view;
    QDockWidget *m_propertyBrowserDock;
    PropertyBrowser *m_propertyBrowser;
};

#endif	/* _EDITORWINDOW_H */

