#include "polylineitem.h"
#include <QPainter>
#include "../componentfactory.h"

PolylineItem::PolylineItem(int id) : GrawItem(id)
{
}

QRectF PolylineItem::boundingRect() const
{
    //return QRectF(0, 0, 40, 40);
    qreal max_x = 0;
    qreal max_y = 0;
    if (ListVyzl.count()>0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            if (max_x < ListVyzl[i]->x())
                max_x = ListVyzl[i]->x();
            if (max_y < ListVyzl[i]->y())
                max_y = ListVyzl[i]->x();
        }
    }else{
        return QRectF(-5, -5, 10, 10);
    }
    return QRectF(0, 0, max_x, max_y);
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    if (ListVyzl.count() == 0) {
        /*painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(-5, -5, 10, 10));*/

        painter->setPen(QPen(Qt::green, 1));
        painter->setBrush(Qt::SolidPattern);
        painter->setBrush(Qt::darkCyan);
        painter->drawEllipse(QRect(-5, -5, 10, 10));
        return;
    }

    if (isSelected())
        paintSelected(painter);
    else
        paintNotSelected(painter);
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
    }else{
        //points.append(QPointF(0, 0));
        //points.append(QPointF(20, 20));
       // points.append(QPointF(40, 0));
    }

    //QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    //painter->drawPolyline(qPts, 3);
    painter->drawPolyline(points);
}

void PolylineItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(-20, -20, 40, 40));

    painter->setPen(QPen(Qt::red, 5));
    painter->setBrush(Qt::NoBrush);

    QVector<QPointF> points;

    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            points.append(QPointF(ListVyzl[i]->x(), ListVyzl[i]->y()));
        }
    }else{
        //points.append(QPointF(0, 0));
        //points.append(QPointF(20, 20));
        //points.append(QPointF(40, 0));
    }

    //QPointF qPts[] = {QPointF(0, 0), QPointF(20, 20), QPointF(40, 0)};
    //painter->drawPolyline(qPts, 3);
    painter->drawPolyline(points);
}

ComponentType PolylineItem::componentType() const
{
    return ComponentType::Polyline;
}

void PolylineItem::AddNewVyzl(const QPointF &pos) {
    GrawItem *newItem = ComponentFactory::createComponent(-1);
    newItem->setPos(pos);
    ListVyzl.append(newItem);
}
