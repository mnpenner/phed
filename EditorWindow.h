/* 
 * File:   EditorWindow.h
 * Author: mark
 *
 * Created on August 11, 2009, 11:20 AM
 */

#ifndef _EDITORWINDOW_H
#define	_EDITORWINDOW_H

#include <QtGui/QtGui>
#include "PropertyBrowser.h"
#include "World.h"

class EditorView;
class PropertiesWindow;

class EditorWindow : public QMainWindow {
    Q_OBJECT

public:
    EditorWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void updateSimAct();

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void mapWasModified();
    void toolSelected(QAction*);
    void toggleSimState();
    void mousePosChanged(const QPointF&);
    void objectsSelected(const QList<Object*>&);

private:
    void createWorld();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void writeSettings();
    void readSettings();

    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QMenu *m_viewMenu;
    QMenu *m_toolsMenu;
    QMenu *m_simMenu;
    QMenu *m_windowsMenu;

    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;
    QToolBar *m_toolsToolBar;
    QToolBar *m_simToolBar;

    QAction *m_newAct;
    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_saveAsAct;
    QAction *m_exitAct;
    QAction *m_aboutAct;
    QAction *m_showGridAct;
    QAction *m_snapToGridAct;

    QAction *m_simStateAct;
    QAction *m_stopSimAct;

    QIcon m_playIcon;
    QIcon m_pauseIcon;
    QString m_playText;
    QString m_pauseText;
    QString m_playStatusTip;
    QString m_pauseStatusTip;

    QActionGroup *m_toolsActGroup;
    QAction *m_selectToolAct;
    QAction *m_ellipseToolAct;
    QAction *m_polygonToolAct;
    QAction *m_rectToolAct;
    QAction *m_edgeToolAct;

    World *m_world;
    EditorView *m_view;
    QDockWidget *m_propertyBrowserDock;
    PropertyBrowser *m_propertyBrowser;
};

#endif	/* _EDITORWINDOW_H */

