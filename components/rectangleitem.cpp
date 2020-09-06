#include "rectangleitem.h"
#include <QPainter>

RectangleItem::RectangleItem(int id) : GrawItem(id)
{
}

QRectF RectangleItem::boundingRect() const
{
    return QRectF(0, 0, 20, 40);
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void RectangleItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    QString ttt("50, 20");
    painter->drawRect(QRect(0, 0, 20, 40));
    painter->drawText(boundingRect(), Qt::AlignCenter, ttt);
}

void RectangleItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 1));
    QString ttt("50, 20");
    painter->drawRect(QRect(0, 0, 20, 40));
    painter->drawText(boundingRect(), Qt::AlignCenter, ttt);
}

ComponentType RectangleItem::componentType() const
{
    return ComponentType::Rectangle;
}
