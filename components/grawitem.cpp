#include "grawitem.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>

GrawItem::GrawItem(int id) : _id(id)
{
    _Propertic = new GrItProperty();
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

void GrawItem::AddPoint()
{

}

void GrawItem::setTypeParent(int iTypeParent)
{
    _type_parent = iTypeParent;
}

int GrawItem::getTypeParent()
{
    return _type_parent;
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

void GrawItem::setFixY(int iFixY)
{

}

void GrawItem::setProperty(const QString ifirst, const QVariant iValue)
{
    _Propertic->setProperty(ifirst, iValue);
    applyProperty();
}

void GrawItem::applyProperty()
{

}

QList<QPair<QString, QString>> GrawItem::getListPropText() const
{
    return _Propertic->getListPropText();
}

QVariant GrawItem::getPropVariant(QString ifirst) const
{
    return _Propertic->getPropVariant(ifirst);
}


void GrawItem::setWidth(int iWidth)
{

}

QByteArray GrawItem::getByteArrCont()
{

}

void GrawItem::setByteArrCont(QByteArray iBAContent)
{

}

void GrawItem::DeleteSelectNode()
{

}

void GrawItem::InsertNode()
{

}

void GrawItem::isUpdateChild()
{

}
