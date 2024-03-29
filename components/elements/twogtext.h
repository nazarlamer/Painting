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
    QGraphicsTextItem *grftxt1;
    QGraphicsTextItem *grftxt2;
    int BoundingRectH = 20;
    int BoundingRectW = 80;
    void setWidth(int iWidth) override;

    GrawItem *NodeWidth;

    QString GrawText1{""};
    QString GrawText2{""};

    void applyProperty() override;

    void setModeView(int iMode) override;

public slots:
    void isUpdateChild() override;

};

