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
    //QString ttt("50, 20 dfgdfg dfgdfgdf ddd");
    //QTextItem *text;
    //text->text()="jhjnnj";
    //QRectF QFontMetricsF::boundingRect(const QString & text)
    //painter->drawText(0,0,ttt);
    //painter->drawText(boundingRect(), Qt::AlignTop, ttt);

    QFont ft;
    ft.setPixelSize(12);
    ft.setBold(true);

    QGraphicsTextItem *qri = new QGraphicsTextItem("dfsad", this);

    qri->setFlag(QGraphicsItem::ItemIsSelectable, false);
    qri->setFlag(QGraphicsItem::ItemIsMovable, false);
    qri->setTextWidth(80);
    qri->setFont(ft);
    qri->paint(painter,option,widget);
    qri->setScale(1);

    QFont ft2;
    ft2.setPixelSize(12);
    ft2.setBold(false);

    QGraphicsTextItem *qri2 = new QGraphicsTextItem("dfsad784554", this);
    qri2->setFlag(QGraphicsItem::ItemIsSelectable, false);
    qri2->setFlag(QGraphicsItem::ItemIsMovable, false);
    qri2->setTextWidth(80);
    qri2->setFont(ft2);
    qri2->setY(qri->boundingRect().height());
    qri2->setScale(1);
     //  painter->drawTextItem(0,0,qri2)
    //qri2->setTransform(trans);
    //qri2->itemTransform(this);

    //qri2->paint(painter,option,widget);


}


