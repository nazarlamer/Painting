#pragma once

#include "../grawitem.h"

class Twogtext: public GrawItem
{
public:
    explicit Twogtext(int id);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // GrawItem interface
public:
    ComponentType componentType() const;
};

