#include "grawitem.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

GrawItem::GrawItem(int id) : _id(id)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

int GrawItem::id() const { return _id; }

QVariant GrawItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //qDebug() << "itemChange";
    if (change == ItemSelectedChange && scene())
        return value;

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

void GrawItem::RotateFlip() {
    setRotation(rotation()+90);
}

bool GrawItem::IsNodesElement() const
{
    if (componentType()==ComponentType::Polyline)
        return true;
    else
        return false;
}

void GrawItem::AddPoint(const QPointF &pos)
{

}

void GrawItem::AddPoint(GrawItem *igi)
{

}

QVector<GrawItem *> GrawItem::GetPoints() const
{

}

void GrawItem::setDeltaX(qreal iDeltaX)
{

}

void GrawItem::setDeltaY(qreal iDeltaY)
{

}

void GrawItem::setPtX(qreal iptX)
{

}

void GrawItem::setPtY(qreal iptY)
{

}

QPointF GrawItem::getPoint() const
{

}

void GrawItem::setParentItem(QGraphicsItem *parent)
{
    QGraphicsItem::setParentItem(parent);
}

void GrawItem::isUpdateChild()
{

}
