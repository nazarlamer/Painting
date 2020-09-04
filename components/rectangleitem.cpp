#include "rectangleitem.h"
#include <QPainter>

RectangleItem::RectangleItem(int id) : GrawItem(id)
{
}

QRectF RectangleItem::boundingRect() const
{
    return QRectF(0, 0, 20, 50);
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    QString ttt("50, 20");
    painter->drawRect(QRect(0, 0, 20, 50));
    painter->drawText(boundingRect(), Qt::AlignCenter, ttt);
}

ComponentType RectangleItem::componentType() const
{
    return ComponentType::Rectangle;
}
