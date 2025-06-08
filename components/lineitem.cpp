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
    if (_ModeView==0) {
        if (isSelected())
            paintSelected(painter);
        else
            paintNotSelected(painter);
    }

    paintMain(painter);
}

void LineItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-10, -10, 20, 20));
}

void LineItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-10, -10, 20, 20));
}

void LineItem::paintMain(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter->drawLine(0, -8, 0, 8);
}

void LineItem::setModeView(int iMode)
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

ComponentType LineItem::componentType() const
{
    return ComponentType::Line;
}


