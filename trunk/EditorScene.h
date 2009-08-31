/* 
 * File:   EditorScene.h
 * Author: mark
 *
 * Created on August 29, 2009, 7:23 PM
 */

#ifndef _EDITORSCENE_H
#define	_EDITORSCENE_H

#include <QtGui/QGraphicsScene>
#include "LineStrip.h"

class EditorScene : public QGraphicsScene {
    Q_OBJECT
    
public:
    enum Tool {
        Select, Scroll, Lasso, Measure,
        Pencil, Pen, Brush, Ellipse, Polygon, Rectangle, EdgeChain,
        RevoluteJoint, PulleyJoint, PrismaticJoint, LineJoint, GearJoint
    };

    EditorScene(QObject *parent = NULL);

signals:
    void mousePosChanged(const QPointF&);

public slots:
    void setTool(Tool tool);
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    Tool m_tool;
    LineStrip m_lineStrip;
    QGraphicsLineItem m_fadeLine;
};

#endif	/* _EDITORSCENE_H */

