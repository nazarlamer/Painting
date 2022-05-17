#include "arrowitem.h"
#include <QPainter>

ArrowItem::ArrowItem(int id) : GrawItem(id)
{
}

QRectF ArrowItem::boundingRect() const
{
    return QRectF(-20, -15, 40, 30);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
}

void ArrowItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -15, 40, 30));
    paintMain(painter);
}

void ArrowItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -15, 40, 30));
    paintMain(painter);
}

void ArrowItem::paintMain(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QVector<QPoint> linemufta;
    linemufta << QPoint(-13, -5) << QPoint(13,-5) << QPoint(0,8);
    painter->drawPolygon(linemufta);

    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter->drawLine(0, -9, 0, -13);
    painter->drawLine(0, 9, 0, 13);
}

ComponentType ArrowItem::componentType() const
{
    return ComponentType::Arrow;
}
