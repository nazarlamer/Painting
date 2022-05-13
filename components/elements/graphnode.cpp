#include "graphnode.h"
#include <QPainter>
#include <QDebug>

GraphNode::GraphNode(int id) : GrawItem(id)
{

}

QRectF GraphNode::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void GraphNode::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-5, -5, 10, 10));
}

void GraphNode::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::cyan, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-5, -5, 10, 10));
}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ptX=x();
    ptY=y();
    emit signalParent();
    QGraphicsItem::mouseReleaseEvent(event);
}

ComponentType GraphNode::componentType() const
{
    return ComponentType::GraphNode;
}

void GraphNode::setDeltaX(qreal iDeltaX)
{
    if (!parentItem()){
        deltaX = iDeltaX;
    }else{
        deltaX = 0;
    }

    setX(ptX+deltaX);
}

void GraphNode::setDeltaY(qreal iDeltaY)
{
    if (!parentItem()){
        deltaY = iDeltaY;
    }else{
        deltaY = 0;
    }

    setY(ptY+deltaY);
}

void GraphNode::setPtX(qreal iptX)
{
    ptX = iptX;
    setX(ptX+deltaX);
}

void GraphNode::setPtY(qreal iptY)
{
    ptY = iptY;
    setY(ptY+deltaY);
}

QPointF GraphNode::getPoint() const
{
    return QPointF(ptX, ptY);
}


