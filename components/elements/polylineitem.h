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
    void AddPoint() override;
    QVector<GrawItem*> GetPoints() const override;
    void DeleteSelectNode() override;
    void InsertNode() override;

private:
    /*QVector<GrawItem*> ListVyzl;*/
    qreal _width = 0;
    qreal _heigth = 0;
    int _penwidth{5};
    QColor _pencolor{Qt::red};

    void paintSelected(QPainter *painter);
    void paintNotSelected(QPainter *painter);
    void UpdateVyzols();
    void paintMain(QPainter *painter);

    void applyProperty() override;

public slots:
    void isUpdateChild() override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

