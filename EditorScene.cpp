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

EditorScene::EditorScene(QObject* parent): QGraphicsScene(parent) {
    QPen pen;
    pen.setColor(QColor(0,0,0,128));
    pen.setStyle(Qt::DotLine);
    m_fadeLine.setPen(pen);

    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch(m_tool) {
        case Polygon:
            if(m_lineStrip.isEmpty()) {
                addItem(&m_lineStrip);
                addItem(&m_fadeLine);
            }
            m_lineStrip.append(mouseEvent->scenePos());
            break;
        default:
            break;
    }
}

void EditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if(!m_lineStrip.isEmpty()) m_fadeLine.setLine(QLineF(m_lineStrip.last(), mouseEvent->scenePos()));
    emit mousePosChanged(mouseEvent->scenePos());
    
}

void EditorScene::setTool(Tool tool) {
    m_tool = tool;
}
