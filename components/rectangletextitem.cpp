#include "rectangletextitem.h"
#include <QPainter>
#include "componentfactory.h"
#include <QDebug>

RectangleTextItem::RectangleTextItem(int id) : GrawItem(id)
{
    NodeWidth = ComponentFactory::createComponent(ComponentType::GraphNode);
    NodeWidth->setParentItem(this);
    NodeWidth->setX(BoundingRectW);
    NodeWidth->setFixY(0);
    connect(NodeWidth, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);

    NodeHeigth = ComponentFactory::createComponent(ComponentType::GraphNode);
    NodeHeigth->setParentItem(this);
    NodeHeigth->setY(BoundingRectH);
    NodeHeigth->setX(BoundingRectW);
    NodeHeigth->setFixX(BoundingRectW);
    connect(NodeHeigth, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);

    grftxt = new QGraphicsTextItem(this);
    QFont fnt = grftxt->font();
    fnt.setBold(false);
    fnt.setPixelSize(12);
    grftxt->setFont(fnt);

    _Propertic->addProperty("TEXT","Текст");
    _Propertic->addProperty("SIZE","Розмір");
    _Propertic->addProperty("BOLD","Грубий");
}

QRectF RectangleTextItem::boundingRect() const
{
    return QRectF(0, 0, BoundingRectW, BoundingRectH);
}

void RectangleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                  QWidget */*widget*/)
{
    if (_ModeView==0) {
        if (isSelected())
            paintSelected(painter);
        else
            paintNotSelected(painter);
    }
    paintMain(painter);
}

void RectangleTextItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->drawRect(QRect(0, 0, BoundingRectW, BoundingRectH));
}

void RectangleTextItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->drawRect(QRect(0, 0, BoundingRectW, BoundingRectH));
}

void RectangleTextItem::paintMain(QPainter *painter)
{
    grftxt->setTextWidth(BoundingRectW);
    grftxt->setPlainText(GrawText);
}

void RectangleTextItem::setWidth(int iWidth)
{
    BoundingRectW = iWidth;
    NodeWidth->setX(BoundingRectW);
}

void RectangleTextItem::setHeight(int iHeight)
{
    BoundingRectH = iHeight;
    NodeHeigth->setY(BoundingRectH);
    NodeHeigth->setFixX(BoundingRectW);
    NodeHeigth->setX(BoundingRectW);
}

void RectangleTextItem::applyProperty()
{
    GrawText = getPropVariant("TEXT").toString();

    if (!getPropVariant("SIZE").isNull()) {
        QFont fnt = grftxt->font();
        fnt.setPixelSize(getPropVariant("SIZE").toInt());
        grftxt->setFont(fnt);
    }
    if (!getPropVariant("BOLD").isNull()) {
        QFont fnt = grftxt->font();
        fnt.setBold(getPropVariant("BOLD").toBool());
        grftxt->setFont(fnt);
    }

    update();
}

void RectangleTextItem::setModeView(int iMode)
{
    if (iMode==0) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    if (iMode==1) {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    NodeWidth->setModeView(iMode);
    NodeHeigth->setModeView(iMode);

    GrawItem::setModeView(iMode);
}

void RectangleTextItem::isUpdateChild()
{
    qDebug() << "RectangleItem :: isUpdateChild";
    if (NodeWidth->x()<10) {
        NodeWidth->setX(10);
        BoundingRectW = 10;
        NodeHeigth->setFixX(10);
        NodeHeigth->setX(10);
    }else{
        BoundingRectW = NodeWidth->x();
        NodeHeigth->setFixX(BoundingRectW);
        NodeHeigth->setX(BoundingRectW);
    }

    if (NodeHeigth->y()<10) {
        NodeHeigth->setY(10);
        BoundingRectH = 10;
    }else{
        BoundingRectH = NodeHeigth->y();
    }

    update();
    emit updScen();
}

ComponentType RectangleTextItem::componentType() const
{
    return ComponentType::RectangleText;
}
