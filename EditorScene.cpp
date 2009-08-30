/* 
 * File:   EditorScene.cpp
 * Author: mark
 * 
 * Created on August 29, 2009, 7:23 PM
 */

#include <qt4/QtGui/qaction.h>
#include <qt4/QtCore/qcoreevent.h>
#include <QtGui/QGraphicsSceneMouseEvent>

#include "EditorScene.h"
#include "Object.h"

EditorScene::EditorScene(QObject* parent): QGraphicsScene(parent) {    
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    mouseEvent->ignore();
}

void EditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    emit mousePosChanged(mouseEvent->scenePos());
}

void EditorScene::setTool(Tool tool) {
    m_tool = tool;
}
