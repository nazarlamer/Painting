#include "grawitem.h"
#include <math.h>

GrawItem::GrawItem(int id) : _id(id)
{
    setFlags(//QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

int GrawItem::id() const { return _id; }

QVariant GrawItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //qDebug() << "itemChange";
    if (change == ItemPositionChange && scene())
    {
        // value is the new position.
        QPointF newPos = value.toPointF();

        int gridSize = 10;
        qreal xV = round(newPos.x()/gridSize)*gridSize;
        qreal yV = round(newPos.y()/gridSize)*gridSize;
        return QPointF(xV, yV);

        //return newPos;
        //return QPointF(xV, yV);

    }
    return QGraphicsItem::itemChange(change, value);
}

void GrawItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    return QGraphicsItem::mousePressEvent(event);
}

void GrawItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(false);
    return QGraphicsItem::mouseReleaseEvent(event);
}
