#pragma once

#include "../grawitem.h"

class GraphVyzol : public GrawItem
{
public:
    explicit GraphVyzol(int id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal x();
    qreal y();

    // GrawItem interface
public:
    ComponentType componentType() const override;
    void setDeltaX(qreal iDeltaX) override;
    void setDeltaY(qreal iDeltaY) override;

private:
    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
    qreal deltaX=0;
    qreal deltaY=0;
};

