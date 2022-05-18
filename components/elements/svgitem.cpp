#include "svgitem.h"
#include <QPainter>

SvgItem::SvgItem(int id) : GrawItem(id)
{

}

QRectF SvgItem::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void SvgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

ComponentType SvgItem::componentType() const
{
    return ComponentType::SvgItem;
}

void SvgItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));
}

void SvgItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));
}
