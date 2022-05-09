#include "graphvyzol.h"
#include <QPainter>
#include <QDebug>

GraphVyzol::GraphVyzol(int id) : GrawItem(id)
{

}

QRectF GraphVyzol::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void GraphVyzol::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void GraphVyzol::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-5, -5, 10, 10));
}

void GraphVyzol::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::cyan, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-5, -5, 10, 10));
}

void GraphVyzol::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "updateparent";
    if (parentItem()) {
        //
        setPtX(x());
        setPtY(y());
        parentItem()->update();
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

ComponentType GraphVyzol::componentType() const
{
    return ComponentType::GraphVyzol;
}

void GraphVyzol::setDeltaX(qreal iDeltaX)
{
    if (!parentItem()){
        deltaX = iDeltaX;
    }else{
        deltaX = 0;
    }

    setX(ptX+deltaX);
}

void GraphVyzol::setDeltaY(qreal iDeltaY)
{
    if (!parentItem()){
        deltaY = iDeltaY;
    }else{
        deltaY = 0;
    }

    setY(ptY+deltaY);
}

void GraphVyzol::setPtX(qreal iptX)
{
    ptX = iptX;
    setX(ptX+deltaX);
}

void GraphVyzol::setPtY(qreal iptY)
{
    ptY = iptY;
    setY(ptY+deltaY);
}

QPointF GraphVyzol::getPoint() const
{
    return QPointF(ptX, ptY);
}
