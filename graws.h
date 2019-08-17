#pragma once

#include "abstractgraw.h"

class Graws: public AbstractGraw
{
public:
    // read about explicit (DELETE THIS COMMENT AFTER READ)
    explicit Graws(int IDElem);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // AbstractGraws interface
public:
    int id() const override;

private:
    int idElem{-1};
};
