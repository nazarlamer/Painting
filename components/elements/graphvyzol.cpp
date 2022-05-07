#include "graphvyzol.h"
#include <QPainter>

GraphVyzol::GraphVyzol(int id) : GrawItem(id)
{

}

QRectF GraphVyzol::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
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
    painter->drawEllipse(QRect(-5, -5, 5, 5));
}

void GraphVyzol::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::cyan, 1));
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(QRect(-5, -5, 5, 5));
}

ComponentType GraphVyzol::componentType() const
{
    return ComponentType::GraphVyzol;
}
