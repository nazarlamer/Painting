#pragma once

#include "grawitem.h"

class CircleItem : public GrawItem
{
public:
    explicit CircleItem(int id);

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
};

