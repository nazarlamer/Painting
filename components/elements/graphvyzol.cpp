#include "graphvyzol.h"
#include <QPainter>

GraphVyzol::GraphVyzol(int id) : GrawItem(id)
{

}

QRectF GraphVyzol::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
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
    painter->setPen(QPen(Qt::blue, 5));
    painter->setBrush(Qt::NoBrush);

    QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    painter->drawPolyline(qPts, 3);
}

void GraphVyzol::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 5));
    painter->setBrush(Qt::NoBrush);

    QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    painter->drawPolyline(qPts, 3);
}

ComponentType GraphVyzol::componentType() const
{
    return ComponentType::GraphVyzol;
}
