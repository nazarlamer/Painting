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
    if (_ModeView==0) {
        if (isSelected())
            paintSelected(painter);
        else
            paintNotSelected(painter);
    }

    paintMain(painter);
}

void ArrowItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());

}

void ArrowItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

void ArrowItem::paintMain(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QVector<QPoint> linemufta;
    linemufta << QPoint(-15, -7) << QPoint(15,-7) << QPoint(0,8);
    painter->drawPolygon(linemufta);

    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter->drawLine(0, -10, 0, -18);
    painter->drawLine(0, 9, 0, 18);
}

void ArrowItem::setModeView(int iMode)
{
    if (iMode==0) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    if (iMode==1) {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    GrawItem::setModeView(iMode);
}

ComponentType ArrowItem::componentType() const
{
    return ComponentType::Arrow;
}
