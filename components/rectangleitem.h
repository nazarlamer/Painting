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

public slots:
    void isUpdateChild() override;

private:
    int BoundingRectH = 40;
    int BoundingRectW = 40;
    GrawItem *NodeSize;
    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
    void paintMain(QPainter *painter);
    void applyProperty() override;
    bool _isFill{false};

    QColor _pencolor{Qt::black};
    QColor _penfill{QColor(255, 237, 176, 255)};
    int _penheight{5};

    int getWidthFromSave() const override;
    int getHeightFromSave() const override;

    void setWidth(int iWidth) override;
    void setHeight(int iHeight) override;

    void setModeView(int iMode) override;

};

