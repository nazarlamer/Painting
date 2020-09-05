#include "circleitem.h"
#include <QPainter>

CircleItem::CircleItem(int id) : GrawItem(id)
{
}

QRectF CircleItem::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

ComponentType CircleItem::componentType() const
{
    return ComponentType::Circle;
}

void CircleItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));

    painter->setPen(QPen(Qt::blue, 3));
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(QRect(-20, -20, 40, 40));
}

void CircleItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));

    painter->setPen(QPen(Qt::red, 3));
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(QRect(-20, -20, 40, 40));
}

