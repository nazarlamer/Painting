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

private:
    void paintSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintNotSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

