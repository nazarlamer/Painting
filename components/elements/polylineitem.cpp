#include "polylineitem.h"
#include <QPainter>

PolylineItem::PolylineItem(int id) : GrawItem(id)
{
}

QRectF PolylineItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void PolylineItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 5));
    painter->setBrush(Qt::NoBrush);

    QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    painter->drawPolyline(qPts, 3);
}

void PolylineItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 5));
    painter->setBrush(Qt::NoBrush);

    QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    painter->drawPolyline(qPts, 3);
}

ComponentType PolylineItem::componentType() const
{
    return ComponentType::Polyline;
}
