#pragma once

#include "grawitem.h"

class RectangleTextItem : public GrawItem
{
public:
    explicit RectangleTextItem(int id);

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

    void setWidth(int iWidth) override;
    void setHeight(int iHeight) override;

    GrawItem *NodeWidth;
    GrawItem *NodeHeigth;

    QString GrawText{""};
    QGraphicsTextItem *grftxt;

    int BoundingRectH = 10;
    int BoundingRectW = 10;

    void applyProperty() override;

    void setModeView(int iMode) override;

public slots:
    void isUpdateChild() override;

};

