#include "svgitem.h"
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QSvgRenderer>

SvgItem::SvgItem(int id) : GrawItem(id)
{
    QSvgRenderer *renderer = new QSvgRenderer(QLatin1String("zap1.svg"));
    QGraphicsSvgItem *svgit = new QGraphicsSvgItem();

    svgit->setSharedRenderer(renderer);
    svgit->setZValue(0);
    svgit->setFlag(QGraphicsItem::ItemIsMovable, false);
    svgit->setFlag(QGraphicsItem::ItemIsSelectable, false);
    svgitem = svgit;
}

QRectF SvgItem::boundingRect() const
{
    return svgitem->boundingRect();
}

void SvgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);

    paintMain(painter, option, widget);
}

ComponentType SvgItem::componentType() const
{
    return ComponentType::SvgItem;
}

void SvgItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(svgitem->boundingRect());
}

void SvgItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(svgitem->boundingRect());
}

void SvgItem::paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    svgitem->paint(painter, option, widget);
}
