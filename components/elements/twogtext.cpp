#include "twogtext.h"
#include <QPainter>
#include <QDebug>
#include <QTextItem>
#include <QGraphicsTextItem>
#include <cmath>

Twogtext::Twogtext(int id) : GrawItem(id)
{
    grftxt1 = new QGraphicsTextItem(this);
    QFont fnt1 = grftxt1->font();
    fnt1.setBold(true);
    fnt1.setPixelSize(12);
    grftxt1->setFont(fnt1);
    grftxt1->setDefaultTextColor(QColor(255,0,0));

    grftxt2 = new QGraphicsTextItem(this);
    QFont fnt2 = grftxt2->font();
    fnt2.setBold(false);
    fnt2.setPixelSize(12);
    grftxt2->setFont(fnt2);
}

QRectF Twogtext::boundingRect() const
{
    return QRectF(0, 0, 80, BoundingRectH);
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
    painter->drawRect(QRect(0, 0, 80, BoundingRectH));
    paintMain(painter,option,widget);
}

void Twogtext::paintNotSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(0, 0, 80, BoundingRectH));
    paintMain(painter,option,widget);
}

void Twogtext::paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(QColor(225,225,225));
    painter->drawRect(boundingRect());

    grftxt1->setTextWidth(80);
    grftxt1->setPlainText("asasas dfgdfg dfgdfgdf bdfgdergerg");
    grftxt2->setTextWidth(80);
    grftxt2->setPlainText("zxxsdsdd xfdgdsfg dxfgdfg sdfgsdgdsfg");
    grftxt2->setY(grftxt1->boundingRect().height());
    qreal heiF = grftxt1->boundingRect().height()+grftxt2->boundingRect().height();
    int hei = round(heiF/10)*10;
    if (hei != BoundingRectH) {
        BoundingRectH=hei;
        update();
    }

}


