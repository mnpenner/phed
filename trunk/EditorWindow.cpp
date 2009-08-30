/* 
 * File:   EditorWindow.cpp
 * Author: mark
 * 
 * Created on August 11, 2009, 11:20 AM
 */

#include <QtGui>
#include "EditorWindow.h"
#include "EditorView.h"
#include "PropertiesWindow.h"

EditorWindow::EditorWindow() {
    Q_INIT_RESOURCE(icons);
    setWindowTitle("Phed");

    createScene();
    createDockWindows();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();
}

void EditorWindow::createScene() {
    m_scene = new EditorScene;
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-5, -5, 10, 10);
    m_view = new QGraphicsView(m_scene);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->scale(1.0, -1.0); // flip coordinate system so that y increases upwards
    m_view->fitInView(-5, -5, 10, 10, Qt::KeepAspectRatio);
    setCentralWidget(m_view);

    connect(m_scene, SIGNAL(mousePosChanged(QPointF)), this, SLOT(mousePosChanged(QPointF)));
}

void EditorWindow::mousePosChanged(QPointF pos) {
    statusBar()->showMessage(tr("%1, %2").arg(pos.x(), 0, 'f', 2).arg(pos.y(), 0, 'f', 2));
}

void EditorWindow::createDockWindows() {
    m_propertyBrowserDock = new QDockWidget(this);
    m_propertyBrowserDock->setObjectName("PropertiesDock");
    m_propertyBrowserDock->setWindowTitle("Properties");
    m_propertyBrowserDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_propertyBrowser = new PropertyBrowser;
    m_propertyBrowserDock->setWidget(m_propertyBrowser);
    addDockWidget(Qt::RightDockWidgetArea, m_propertyBrowserDock);
}

void EditorWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void EditorWindow::writeSettings() {
    QSettings settings;
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());
}

void EditorWindow::readSettings() {
    QSettings settings;
    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());
}

void EditorWindow::createActions() {
    newAct = new QAction(QIcon(":/icons/silk/page_white.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new map"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/icons/silk/folder_page_white.png"), tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing map"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/icons/silk/disk.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the map to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the map under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    showGridAct = new QAction(tr("Show &Grid"), this);
    showGridAct->setShortcut(tr("Ctrl+G"));
    showGridAct->setStatusTip(tr("Display a grid over the map"));
    showGridAct->setCheckable(true);
    //connect(showGridAct, SIGNAL(toggled(bool)), editorView, SLOT(showGrid(bool)));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    toolsActGroup = new QActionGroup(this);
    toolsActGroup->setExclusive(true);

    selectToolAct = new QAction(QIcon(":/icons/custom/select.png"), tr("&Select"), toolsActGroup);
    selectToolAct->setIconVisibleInMenu(false);
    selectToolAct->setShortcut(Qt::Key_S);
    selectToolAct->setCheckable(true);
    selectToolAct->setStatusTip(tr("Select objects to modify or delete"));
    selectToolAct->setProperty("tool", EditorScene::Select);
    selectToolAct->setChecked(true);

    circleToolAct = new QAction(QIcon(":/icons/custom/ellipse.png"), tr("&Ellipse"), toolsActGroup);
    circleToolAct->setIconVisibleInMenu(false);
    circleToolAct->setShortcut(Qt::Key_E);
    circleToolAct->setCheckable(true);
    circleToolAct->setStatusTip(tr("Draw ellipse objects"));
    circleToolAct->setProperty("tool", EditorScene::Ellipse);

    polygonToolAct = new QAction(QIcon(":/icons/custom/polygon.png"), tr("&Polygon"), toolsActGroup);
    polygonToolAct->setIconVisibleInMenu(false);
    polygonToolAct->setShortcut(Qt::Key_P);
    polygonToolAct->setCheckable(true);
    polygonToolAct->setStatusTip(tr("Draw polygonal objects"));
    polygonToolAct->setProperty("tool", EditorScene::Polygon);

    rectToolAct = new QAction(QIcon(":/icons/custom/rectangle.png"), tr("&Rectangle"), toolsActGroup);
    rectToolAct->setIconVisibleInMenu(false);
    rectToolAct->setShortcut(Qt::Key_R);
    rectToolAct->setCheckable(true);
    rectToolAct->setStatusTip(tr("Draw rectangle objects"));
    rectToolAct->setProperty("tool", EditorScene::Rectangle);

    lineToolAct = new QAction(QIcon(":/icons/custom/line.png"), tr("&Line"), toolsActGroup);
    lineToolAct->setIconVisibleInMenu(false);
    lineToolAct->setShortcut(Qt::Key_L);
    lineToolAct->setCheckable(true);
    lineToolAct->setStatusTip(tr("Draw lines"));
    lineToolAct->setProperty("tool", EditorScene::EdgeChain);

    connect(toolsActGroup, SIGNAL(selected(QAction*)), this, SLOT(toolSelected(QAction*)));


    controlActGroup = new QActionGroup(this);
    controlActGroup->setExclusive(true);

    playAct = new QAction(QIcon(":/icons/custom/media-playback-start.png"), tr("&Run"), controlActGroup);
    playAct->setShortcut(Qt::Key_Space);
    playAct->setCheckable(true);
    playAct->setStatusTip(tr("Run physics"));
    //connect(playAct, SIGNAL(triggered()), editorView, SLOT(runPhysics()));

    pauseAct = new QAction(QIcon(":/icons/custom/media-playback-pause.png"), tr("&Pause"), controlActGroup);
    pauseAct->setShortcut(Qt::Key_Space);
    pauseAct->setCheckable(true);
    pauseAct->setStatusTip(tr("Pause physics"));
    //connect(pauseAct, SIGNAL(triggered()), editorView, SLOT(pausePhysics()));

    connect(playAct, SIGNAL(toggled(bool)), pauseAct, SLOT(setVisible(bool))); // TODO: just swap the icon instead, and use one signal?
    connect(pauseAct, SIGNAL(toggled(bool)), playAct, SLOT(setVisible(bool)));
    pauseAct->setChecked(true);
    pauseAct->setVisible(false);
}

void EditorWindow::toolSelected(QAction* act) {
    m_scene->setTool((EditorScene::Tool)act->property("tool").toInt());
}

void EditorWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(showGridAct);

    controlMenu = menuBar()->addMenu(tr("&Control"));
    controlMenu->addAction(playAct);
    controlMenu->addAction(pauseAct);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(selectToolAct);
    toolsMenu->addAction(circleToolAct);
    toolsMenu->addAction(rectToolAct);
    toolsMenu->addAction(polygonToolAct);
    toolsMenu->addAction(lineToolAct);

    windowsMenu = menuBar()->addMenu(tr("&Window"));
    windowsMenu->addAction(m_propertyBrowserDock->toggleViewAction());

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void EditorWindow::createToolBars() {
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setObjectName("FileToolBar");
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    controlToolBar = addToolBar(tr("Controls"));
    controlToolBar->setObjectName("ControlToolBar");
    controlToolBar->addAction(playAct);
    controlToolBar->addAction(pauseAct);

    toolsToolBar = addToolBar(tr("Tools"));
    toolsToolBar->setObjectName("ToolsToolBar");
    toolsToolBar->addAction(selectToolAct);
    toolsToolBar->addAction(circleToolAct);
    toolsToolBar->addAction(rectToolAct);
    toolsToolBar->addAction(polygonToolAct);
    toolsToolBar->addAction(lineToolAct);
}

void EditorWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

void EditorWindow::newFile() {
}

void EditorWindow::open() {
}

bool EditorWindow::save() {
    return false;
}

bool EditorWindow::saveAs() {
    return false;
}

void EditorWindow::about() {
    QMessageBox::about(this, "About Q2D", "<b>Q2D</b> is a Box2D map editor written by Mark Bayazit.");
}

void EditorWindow::mapWasModified() {
}
