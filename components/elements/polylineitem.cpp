#include "polylineitem.h"
#include <QPainter>
/*Не коректне підключення хідер файла.*/
#include "../componentfactory.h"
#include <QDebug>

PolylineItem::PolylineItem(int id) : GrawItem(id)
{
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);

    _Propertic->addProperty("COLOR","Колір");
    _Propertic->addProperty("WIDTH2","Товщина");
}

QRectF PolylineItem::boundingRect() const
{
    //qDebug() << "boundingRect";
    qreal max_x = 0;
    qreal max_y = 0;
    if (ListVyzl.count()>0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            if (max_x < ListVyzl[i]->getPoint().x())
                max_x = ListVyzl[i]->getPoint().x();
            if (max_y < ListVyzl[i]->getPoint().y())
                max_y = ListVyzl[i]->getPoint().y();
        }
        return QRectF(0-_penwidth, 0-_penwidth, max_x+_penwidth*2, max_y+_penwidth*2);
    }else {
        return QRectF(-5, -5, 10, 10);
    }
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    //qDebug() << "paint";
    if (ListVyzl.count() == 0) {
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
}

void PolylineItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, _penwidth));
    painter->setBrush(Qt::NoBrush);
    paintMain(painter);
}

void PolylineItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(_pencolor, _penwidth));
    painter->setBrush(Qt::NoBrush);
    paintMain(painter);
}

void PolylineItem::UpdateVyzols()
{
    qreal deltx = 0;
    qreal delty = 0;
    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            if (ListVyzl[i]->x()<0) {
                if (ListVyzl[i]->x()<deltx)
                    deltx = ListVyzl[i]->x();

            }
            if (ListVyzl[i]->y()<0) {
                if (ListVyzl[i]->y()<delty)
                    delty = ListVyzl[i]->y();
            }
        }
    }

    deltx = deltx * -1;
    delty = delty * -1;
    if (deltx>0 or delty>0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setPtX(ListVyzl[i]->getPoint().x()+deltx);
            ListVyzl[i]->setPtY(ListVyzl[i]->getPoint().y()+delty);
        }

        setX(x()-deltx);
        setY(y()-delty);
    }

    deltx = boundingRect().width();
    delty = boundingRect().height();

    if (ListVyzl.count() > 0) {

        for (int i=0; i<ListVyzl.count(); i++) {

            if (ListVyzl[i]->x()<deltx)
                deltx = ListVyzl[i]->x();

            if (ListVyzl[i]->y()<delty)
                delty = ListVyzl[i]->y();
        }
    }

    if (deltx>0 or delty>0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setPtX(ListVyzl[i]->getPoint().x()-deltx);
            ListVyzl[i]->setPtY(ListVyzl[i]->getPoint().y()-delty);
        }

        setX(x()+deltx);
        setY(y()+delty);
    }

    emit updScen();
}

void PolylineItem::paintMain(QPainter *painter)
{
    QVector<QPointF> points;
    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            points.append(ListVyzl[i]->getPoint());
        }
    }
    painter->drawPolyline(points);
}

void PolylineItem::applyProperty()
{
    if (!getPropVariant("COLOR").isNull())
        _pencolor = getPropVariant("COLOR").value<QColor>();

    if (!getPropVariant("WIDTH2").isNull())
        _penwidth = getPropVariant("WIDTH2").toInt();

    update();
}

void PolylineItem::isUpdateChild()
{
    qDebug() << "PolylineItem :: isUpdateChild";
    update();
    UpdateVyzols();
}

void PolylineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouseMoveEvent";
    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setDeltaX(pos().x());
            ListVyzl[i]->setDeltaY(pos().y());
        }
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void PolylineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setDeltaX(pos().x());
            ListVyzl[i]->setDeltaY(pos().y());
        }
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

ComponentType PolylineItem::componentType() const
{
    return ComponentType::Polyline;
}

void PolylineItem::AddPoint(const QPointF &iPos)
{
    if (ListVyzl.count() == 0) {
        GrawItem *newItemZero = ComponentFactory::createComponent(ComponentType::GraphNode);
        newItemZero->setDeltaX(pos().x());
        newItemZero->setDeltaY(pos().y());
        ListVyzl.append(newItemZero);
    }

    GrawItem *newItem = ComponentFactory::createComponent(ComponentType::GraphNode);
    QPointF newpos = iPos;

    qreal deltx = 0;
    qreal delty = 0;

    if (iPos.x()<pos().x() or iPos.y()<pos().y()) {
        if (ListVyzl.count() > 0) {
            if (newpos.x()<pos().x()) {
                deltx = pos().x()-newpos.x();
                for (int i=0; i<ListVyzl.count(); i++) {
                    ListVyzl[i]->setPtX(ListVyzl[i]->getPoint().x()+deltx);
                    ListVyzl[i]->setDeltaX(pos().x()-deltx);
                }
            }
            if (newpos.y()<pos().y()) {
                delty = pos().y()-newpos.y();
                for (int i=0; i<ListVyzl.count(); i++) {
                    ListVyzl[i]->setPtY(ListVyzl[i]->getPoint().y()+delty);
                    ListVyzl[i]->setDeltaY(pos().y()-delty);
                }
            }
        }
    }

    newItem->setPtX(iPos.x()-pos().x()+deltx);
    newItem->setPtY(iPos.y()-pos().y()+delty);
    newItem->setDeltaX(pos().x()-deltx);
    newItem->setDeltaY(pos().y()-delty);

    ListVyzl.append(newItem);

    setX(pos().x()-deltx);
    setY(pos().y()-delty);
}

void PolylineItem::AddPoint(GrawItem *igi)
{
    ListVyzl.append(igi);
}

QVector<GrawItem*>PolylineItem::GetPoints() const
{
    //qDebug() << "PolylineItem : :GetPoints()";
    for (int i=0; i<ListVyzl.count(); i++) {
        ListVyzl[i]->setDeltaX(x());
        ListVyzl[i]->setDeltaY(y());
    }

    return ListVyzl;
}
