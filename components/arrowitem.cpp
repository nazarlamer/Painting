#include "arrowitem.h"
#include <QPainter>

ArrowItem::ArrowItem(int id) : GrawItem(id)
{
}

QRectF ArrowItem::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));

    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QVector<QPoint> linemufta;
    linemufta << QPoint(-15, -10) << QPoint(15,-10) << QPoint(0,6);
    painter->drawPolygon(linemufta);

    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter->drawLine(0, -11, 0, -18);
    painter->drawLine(0, 10, 0, 18);
}

ComponentType ArrowItem::componentType() const
{
    return ComponentType::Arrow;
}
