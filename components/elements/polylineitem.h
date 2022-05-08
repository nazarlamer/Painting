#pragma once

#include "../grawitem.h"
#include <QVector>

class PolylineItem : public GrawItem
{
public:
    explicit PolylineItem(int id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // GrawItem interface
public:
    ComponentType componentType() const override;
    void AddPoint(const QPointF &iPos) override;

private:
    QVector<GrawItem*> ListVyzl;

    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
};

