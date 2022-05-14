#pragma once

#include "grawitem.h"

class ArrowItem : public GrawItem
{
public:
    explicit ArrowItem(int id);

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
    void paintMain(QPainter *painter);

};

