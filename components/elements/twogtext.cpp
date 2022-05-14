#include "twogtext.h"
#include <QPainter>
#include <QDebug>
#include <QTextItem>
#include <QGraphicsTextItem>

Twogtext::Twogtext(int id) : GrawItem(id)
{

}

QRectF Twogtext::boundingRect() const
{
    return QRectF(0, 0, 80, 60);
}

void Twogtext::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected())
        paintSelected(painter,option,widget);
    else
        paintNotSelected(painter,option,widget);
}

ComponentType Twogtext::componentType() const
{
    return ComponentType::TwoText;
}

void Twogtext::paintSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(0, 0, 80, 60));
    paintMain(painter,option,widget);
}

void Twogtext::paintNotSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(0, 0, 80, 60));
    paintMain(painter,option,widget);
}

void Twogtext::paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*QString ttt("50, 20 dfgdfg dfgdfgdf ddd");
    QTextItem *text;
    //text->text()="jhjnnj";
    //QRectF QFontMetricsF::boundingRect(const QString & text)
    painter->drawText(0,0,ttt);
    painter->drawText(boundingRect(), Qt::AlignTop, ttt);*/

    QGraphicsTextItem *qri = new QGraphicsTextItem("dfsad00");
    qri->setFlag(QGraphicsItem::ItemIsSelectable, false);
    qri->setFlag(QGraphicsItem::ItemIsMovable, false);
    qri->setTextWidth(80);
    qri->font().setBold(true);
    qri->font().setPointSizeF(8);
    qri->paint(painter,option,widget);

    QGraphicsTextItem *qri2 = new QGraphicsTextItem("dfsad00", this);
    qri2->setFlag(QGraphicsItem::ItemIsSelectable, false);
    qri2->setFlag(QGraphicsItem::ItemIsMovable, false);
    qri2->setTextWidth(80);
    qri2->font().setBold(true);
    qri2->font().setPointSizeF(8);
    qri2->setY(qri->boundingRect().height());

}


