#include <QtDebug>

#include "mainscene.h"

void MainScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (!event->modifiers().testFlag(Qt::ControlModifier))
    {
        event->ignore();
        return;
    }
    if (event->delta() > 0)
    {
        emit zoomIn();
    }
    else
    {
        emit zoomOut();
    }
    event->accept();
}

void MainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "MainScene::mouseMoveEvent" << event->scenePos();
}
