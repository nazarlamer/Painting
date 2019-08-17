#pragma once

#include "grawitem.h"

class Graws: public GrawItem
{
public:

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};
