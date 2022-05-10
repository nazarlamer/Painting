#pragma once

#include "grawitem.h"

class RectangleItem : public GrawItem
{
public:
    explicit RectangleItem(int id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // GrawItem interface
public:
    ComponentType componentType() const override;

signals:
   void signalParent();

private:
    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
};

