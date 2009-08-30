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
#include "LineStrip.h"

EditorScene::EditorScene(QObject* parent): QGraphicsScene(parent), m_lineStrip(NULL) {
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch(m_tool) {
        case Polygon:
            if(m_lineStrip == NULL) {
                m_lineStrip = new LineStrip;
                addItem(m_lineStrip);
            }
            m_lineStrip->add(mouseEvent->scenePos());
            break;
        default:
            break;
    }
}

void EditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    emit mousePosChanged(mouseEvent->scenePos());
}

void EditorScene::setTool(Tool tool) {
    m_tool = tool;
}
