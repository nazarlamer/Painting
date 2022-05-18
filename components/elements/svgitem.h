#pragma once

#include "../grawitem.h"

#include <qgraphicssvgitem.h>

class SvgItem : public GrawItem
{
public:
    explicit SvgItem(int id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // GrawItem interface
public:
    ComponentType componentType() const override;

private:
    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
    void paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsSvgItem *svgitem;
};

