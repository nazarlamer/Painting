/*Ще не остаточна версія Ітема*/
#pragma once

#include "../grawitem.h"

class GraphNode : public GrawItem
{
public:
    explicit GraphNode(int id);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // GrawItem interface

public:
    ComponentType componentType() const override;
    /*void setDeltaX(qreal iDeltaX) override;
    void setDeltaY(qreal iDeltaY) override;
    void setPtX(qreal iptX) override;
    void setPtY(qreal iptY) override;*/
    QPointF getPoint() const override;
    void setFixY(int iFixY) override;
    void setFixX(int iFixX) override;

private:
    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
    qreal deltaX=0;
    qreal deltaY=0;
    qreal ptX=0;
    qreal ptY=0;
    int _fixY=-1;
    int _fixX=-1;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

