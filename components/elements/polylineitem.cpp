#include "polylineitem.h"
#include <QPainter>
#include "../componentfactory.h"
#include <QDebug>

PolylineItem::PolylineItem(int id) : GrawItem(id)
{

}

QRectF PolylineItem::boundingRect() const
{
    qreal max_x = 0;
    qreal max_y = 0;
    if (ListVyzl.count()>0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            if (max_x < ListVyzl[i]->x())
                max_x = ListVyzl[i]->x();
            if (max_y < ListVyzl[i]->y())
                max_y = ListVyzl[i]->y();
        }
        return QRectF(0, 0, max_x, max_y);
    }else {
        return QRectF(-5, -5, 10, 10);
    }

}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (ListVyzl.count() == 0) {
        //painter->setPen(QPen(Qt::red, 1));
        //painter->setBrush(Qt::NoBrush);
        //painter->drawRect(QRect(-5, -5, 10, 10));

        painter->setPen(QPen(Qt::green, 1));
        painter->setBrush(Qt::SolidPattern);
        painter->setBrush(Qt::darkCyan);
        painter->drawEllipse(QRect(-5, -5, 10, 10));
        return;
    }else{
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);

    if (ListVyzl.count() > 0) {

    }
}

void PolylineItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 5));
    painter->setBrush(Qt::NoBrush);

    QVector<QPointF> points;

    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            points.append(QPointF(ListVyzl[i]->x(), ListVyzl[i]->y()));
        }
    }
    painter->drawPolyline(points);
}

void PolylineItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 5));
    painter->setBrush(Qt::NoBrush);

    QVector<QPointF> points;

    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            points.append(QPointF(ListVyzl[i]->x(), ListVyzl[i]->y()));
        }
    }
    painter->drawPolyline(points);
}

ComponentType PolylineItem::componentType() const
{
    return ComponentType::Polyline;
}

void PolylineItem::AddPoint(const QPointF &iPos)
{
    if (ListVyzl.count() == 0) {
        GrawItem *newItemZero = ComponentFactory::createComponent(ComponentType::GraphVyzol);
        ListVyzl.append(newItemZero);
    }

    GrawItem *newItem = ComponentFactory::createComponent(ComponentType::GraphVyzol);
    QPointF newpos = iPos;

    qreal deltx = 0;
    qreal delty = 0;

    if (iPos.x()<pos().x() or iPos.y()<pos().y()) {
        if (ListVyzl.count() > 0) {
            if (newpos.x()<pos().x()) {
                deltx = pos().x()-newpos.x();
                for (int i=0; i<ListVyzl.count(); i++)
                    ListVyzl[i]->setX(ListVyzl[i]->x()+deltx);
            }
            if (newpos.y()<pos().y()) {
                delty = pos().y()-newpos.y();
                for (int i=0; i<ListVyzl.count(); i++)
                    ListVyzl[i]->setY(ListVyzl[i]->y()+delty);
            }
        }
    }

    newpos.setX(iPos.x()-pos().x()+deltx);
    newpos.setY(iPos.y()-pos().y()+delty);

    newItem->setPos(newpos);
    ListVyzl.append(newItem);


    setX(pos().x()-deltx);
    setY(pos().y()-delty);
}
