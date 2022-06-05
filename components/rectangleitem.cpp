#include "rectangleitem.h"
#include <QPainter>
#include "componentfactory.h"
#include <QDebug>

RectangleItem::RectangleItem(int id) : GrawItem(id)
{
    NodeSize = ComponentFactory::createComponent(ComponentType::GraphNode);
    NodeSize->setParentItem(this);
    NodeSize->setX(BoundingRectW);
    NodeSize->setY(BoundingRectH);
    connect(NodeSize, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);

    _Propertic->addProperty("HEIGHT","Товщина лінії");
    _Propertic->addProperty("COLOR","Колір лінії");
    _Propertic->addProperty("FILLB","Заливка");
    _Propertic->addProperty("FILL","Колір заливки");
}

QRectF RectangleItem::boundingRect() const
{
    return QRectF(0-_penheight, 0-_penheight, BoundingRectW+_penheight*2, BoundingRectH+_penheight*2);
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    paintMain(painter);

    if (_ModeView==0) {
        if (isSelected())
            paintSelected(painter);
    }
    //else
    //    paintNotSelected(painter);
}

void RectangleItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->drawRect(QRect(0, 0, BoundingRectW, BoundingRectH));
}

void RectangleItem::paintNotSelected(QPainter *painter)
{
    //painter->setPen(QPen(Qt::black, 1));
    //painter->drawRect(QRect(0, 0, 40, 40));
}

void RectangleItem::paintMain(QPainter *painter)
{
    painter->setPen(QPen(_pencolor, _penheight, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    if (_isFill) {
        QPainterPath path;
        path.addRoundedRect(QRectF(0, 0, BoundingRectW, BoundingRectH), 0, 0);
        painter->fillPath(path, _penfill);
    }
    painter->drawRect(QRect(0, 0, BoundingRectW, BoundingRectH));
}

void RectangleItem::isUpdateChild()
{
    qDebug() << "RectangleItem :: isUpdateChild";
    if (NodeSize->x()<10) {
        NodeSize->setX(10);
        BoundingRectW = 10;
    }else{
        BoundingRectW = NodeSize->x();
    }

    if (NodeSize->y()<10) {
        NodeSize->setY(10);
        BoundingRectH = 10;
    }else{
        BoundingRectH = NodeSize->y();
    }

    update();
    emit updScen();
}

void RectangleItem::applyProperty()
{
    if (!getPropVariant("COLOR").isNull())
        _pencolor = getPropVariant("COLOR").value<QColor>();

    if (!getPropVariant("HEIGHT").isNull())
        _penheight = getPropVariant("HEIGHT").toInt();

    if (!getPropVariant("FILLB").isNull())
        _isFill = getPropVariant("FILLB").toBool();

    if (!getPropVariant("FILL").isNull())
        _penfill = getPropVariant("FILL").value<QColor>();

    update();
}

int RectangleItem::getWidthFromSave() const
{
    return BoundingRectW;
}

int RectangleItem::getHeightFromSave() const
{
    return BoundingRectH;
}

void RectangleItem::setWidth(int iWidth)
{
    BoundingRectW = iWidth;
    NodeSize->setX(BoundingRectW);
}

void RectangleItem::setHeight(int iHeight)
{
    BoundingRectH = iHeight;
    NodeSize->setY(BoundingRectH);
}

void RectangleItem::setModeView(int iMode)
{
    if (iMode==0) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    if (iMode==1) {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    GrawItem::setModeView(iMode);
}

ComponentType RectangleItem::componentType() const
{
    return ComponentType::Rectangle;
}
