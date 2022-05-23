/*Ще не остаточна версія Ітема*/
#include "graphnode.h"
#include <QPainter>
#include <QDebug>

GraphNode::GraphNode(int id) : GrawItem(id)
{

}

QRectF GraphNode::boundingRect() const
{
    if (_ModeView==0)
        return QRectF(-4, -4, 8, 8);
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (_ModeView!=0)
        return;

    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void GraphNode::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-4, -4, 8, 8));
}

void GraphNode::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::cyan, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-4, -4, 8, 8));
}


void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ptX=x();
    ptY=y();
    emit signalParent();
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if (_fixY>=0)
        setY(_fixY);
}

ComponentType GraphNode::componentType() const
{
    return ComponentType::GraphNode;
}

/*void GraphNode::setDeltaX(qreal iDeltaX)
{
    if (!parentItem()){
        deltaX = iDeltaX;
    }else{
        deltaX = 0;
    }

    setX(ptX+deltaX);
}*/

/*
В чому різниця між setDelta і setPt функціями? Чи не можна було в клієнтському коді порахувати потрібні
зміщення і передати результат стандартним методам setX, setY?

consty qreal deltaForX = calculateDeltaForX();
consty qreal deltaForY = calculateDeltaForY();
item->setX(deltaForX);
item->setY(deltaForY);
 */

/*void GraphNode::setDeltaY(qreal iDeltaY)
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
}*/

/*
Цей метод вертає точку на що, на середину фігури чи її низ(верх)???
Що має думати клієнгт при такому виклику:
circle->getPoint(); ???
*/
QPointF GraphNode::getPoint() const
{
    //qDebug() << "GraphNode::getPoint() 111";
    return QPointF(ptX, ptY);
}

void GraphNode::setFixY(int iFixY)
{
    _fixY = iFixY;
}


