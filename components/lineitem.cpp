#include "lineitem.h"
#include <QPainter>

LineItem::LineItem(int id) : GrawItem(id)
{
}

QRectF LineItem::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                     QWidget */*widget*/)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-10, -10, 20, 20));

    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter->drawLine(0, -8, 0, 8);

    //QTransform t;
    //t.rotate(90);
    setRotation(90);
}

ComponentType LineItem::componentType() const
{
    return ComponentType::Line;
}
