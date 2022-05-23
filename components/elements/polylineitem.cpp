#include "polylineitem.h"
#include <QPainter>
/*Не коректне підключення хідер файла. ???*/
#include "../componentfactory.h"
#include <QDebug>

PolylineItem::PolylineItem(int id) : GrawItem(id)
{
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);

    _Propertic->addProperty("COLOR","Колір");
    _Propertic->addProperty("WIDTH2","Товщина");

    //GrawItem *newItemZero = ComponentFactory::createComponent(ComponentType::GraphNode);
    //newItemZero->setParent(this);
}

QRectF PolylineItem::boundingRect() const
{
    //return QRectF(nullptr_t);
    //qDebug() << "boundingRect";
    qreal max_x = 0;
    qreal max_y = 0;
    //if (ListVyzl.count()>0) {
    if (this->childItems().count()>0) {
        for (QGraphicsItem *itm: this->childItems()) {
            GrawItem *gitm = dynamic_cast<GrawItem*>(itm);

            //this->childItems().at(i)
            //arrp.append(dynamic_cast<GrawItem*>(itm));
        /*for (int i=0; i<ListVyzl.count(); i++)
        {
            if (max_x < ListVyzl[i]->getPoint().x())
                max_x = ListVyzl[i]->getPoint().x();
            if (max_y < ListVyzl[i]->getPoint().y())
                max_y = ListVyzl[i]->getPoint().y();*/

            if (max_x < gitm->x())
                max_x = gitm->x();
            if (max_y < gitm->y())
                max_y = gitm->y();
        }
        return QRectF(0-_penwidth, 0-_penwidth, max_x+_penwidth*2, max_y+_penwidth*2);
    }else {
        return QRectF(-5, -5, 10, 10);
    }
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
                      QWidget */*widget*/)
{
    //return;
    //qDebug() << "paint";
    //if (ListVyzl.count() == 0) {
    if (this->childItems().count()==0) {
        painter->setPen(QPen(Qt::green, 1));
        painter->setBrush(Qt::SolidPattern);
        painter->setBrush(Qt::darkCyan);
        painter->drawEllipse(QRect(-5, -5, 10, 10));
        return;
    }else{
        if (_ModeView==0) {
            painter->setPen(QPen(Qt::red, 1));
            painter->setBrush(Qt::NoBrush);
            painter->drawRect(boundingRect());
        }
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
    if (this->childItems().count() > 0) {
        for (QGraphicsItem *itm: this->childItems()) {
            GrawItem *gitm = dynamic_cast<GrawItem*>(itm);

            if (gitm->x()<0) {
                if (gitm->x()<deltx)
                    deltx = gitm->x();
            }
            if (gitm->y()<0) {
                if (gitm->y()<delty)
                    delty = gitm->y();
            }
        }
    }

    deltx = deltx * -1;
    delty = delty * -1;

    if (deltx>0 or delty>0) {
        for (QGraphicsItem *itm: this->childItems()) {
            GrawItem *gitm = dynamic_cast<GrawItem*>(itm);

            //ListVyzl[i]->setPtX(ListVyzl[i]->getPoint().x()+deltx);
            //ListVyzl[i]->setPtY(ListVyzl[i]->getPoint().y()+delty);

            gitm->setX(gitm->x()+deltx);
            gitm->setY(gitm->y()+delty);
        }

        setX(x()-deltx);
        setY(y()-delty);
    }

    deltx = boundingRect().width();
    delty = boundingRect().height();

    if (this->childItems().count() > 0) {
        for (QGraphicsItem *itm: this->childItems()) {
            GrawItem *gitm = dynamic_cast<GrawItem*>(itm);

            if (gitm->x()<deltx)
                deltx = gitm->x();

            if (gitm->y()<delty)
                delty = gitm->y();
        }
    }

    if (deltx>0 or delty>0) {
        for (QGraphicsItem *itm: this->childItems()) {
            GrawItem *gitm = dynamic_cast<GrawItem*>(itm);
            gitm->setX(gitm->x()-deltx);
            gitm->setY(gitm->y()-delty);
        }

        setX(x()+deltx);
        setY(y()+delty);
    }

    emit updScen();
}

void PolylineItem::paintMain(QPainter *painter)
{
    QVector<QPointF> points;
    /*if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++)
        {
            points.append(ListVyzl[i]->getPoint());
        }
    }*/
    for (QGraphicsItem *itm: this->childItems()) {
        //this->childItems().at(i)
        points.append(dynamic_cast<GrawItem*>(itm)->pos());
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
    /*if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setDeltaX(pos().x());
            ListVyzl[i]->setDeltaY(pos().y());
        }
    }*/
    QGraphicsItem::mouseMoveEvent(event);
}

void PolylineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    /*if (ListVyzl.count() > 0) {
        for (int i=0; i<ListVyzl.count(); i++) {
            ListVyzl[i]->setDeltaX(pos().x());
            ListVyzl[i]->setDeltaY(pos().y());
        }
    }*/

    QGraphicsItem::mouseReleaseEvent(event);
}

ComponentType PolylineItem::componentType() const
{
    return ComponentType::Polyline;
}

void PolylineItem::AddPoint(const QPointF &iPos)
{
    /*if (ListVyzl.count() == 0) {
        GrawItem *newItemZero = ComponentFactory::createComponent(ComponentType::GraphNode);
        //newItemZero->setDeltaX(pos().x());
        //newItemZero->setDeltaY(pos().y());
        //ListVyzl.append(newItemZero);
        newItemZero->setParent(this);
    }*/

    QPointF newpos = iPos;

    GrawItem *newItem = ComponentFactory::createComponent(ComponentType::GraphNode);
    newItem->setParentItem(this);
    newItem->setX(iPos.x()-this->x());
    newItem->setY(iPos.y()-this->y());

    qreal deltx = 0;
    qreal delty = 0;

    if (iPos.x()<pos().x() or iPos.y()<pos().y()) {
        //if (ListVyzl.count() > 0) {
        if (this->childItems().count() > 0) {
            if (newpos.x()<pos().x()) {
                deltx = pos().x()-newpos.x();
                //for (int i=0; i<ListVyzl.count(); i++) {
                for (QGraphicsItem *itm: this->childItems()) {
                    GrawItem *gitm = dynamic_cast<GrawItem*>(itm);
                    gitm->setX(gitm->x()+deltx);
                    //ListVyzl[i]->setPtX(ListVyzl[i]->getPoint().x()+deltx);
                    //ListVyzl[i]->setDeltaX(pos().x()-deltx);
                }
            }
            if (newpos.y()<pos().y()) {
                delty = pos().y()-newpos.y();
                //for (int i=0; i<ListVyzl.count(); i++) {
                for (QGraphicsItem *itm: this->childItems()) {
                    GrawItem *gitm = dynamic_cast<GrawItem*>(itm);
                    gitm->setY(gitm->y()+delty);
                    //ListVyzl[i]->setPtY(ListVyzl[i]->getPoint().y()+delty);
                    //ListVyzl[i]->setDeltaY(pos().y()-delty);
                }
            }
        }
    }

    connect(newItem, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);

    //update();

    /*newItem->setPtX(iPos.x()-pos().x()+deltx);
    newItem->setPtY(iPos.y()-pos().y()+delty);
    newItem->setDeltaX(pos().x()-deltx);
    newItem->setDeltaY(pos().y()-delty);*/

    /*ListVyzl.append(newItem);*/

    setX(pos().x()-deltx);
    setY(pos().y()-delty);
}

void PolylineItem::AddPoint()
{
    GrawItem *newItem = ComponentFactory::createComponent(ComponentType::GraphNode);
    newItem->setParentItem(this);
    connect(newItem, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);
}

QVector<GrawItem*>PolylineItem::GetPoints() const
{
    QVector<GrawItem*> arrp;
    //for(int i=0; i<this->children().count();i++) {
    //    QObject *item = this->children().at(i);
    for (QGraphicsItem *itm: this->childItems()) {
        //this->childItems().at(i)
        arrp.append(dynamic_cast<GrawItem*>(itm));
        //for (const QList<QGraphicsItem*> itm: this->childItems()) {

            //qDebug() << "PolylineItem : :GetPoints()";
            //return this.children();
            /*for (int i=0; i<ListVyzl.count(); i++) {
                ListVyzl[i]->setDeltaX(x());
                ListVyzl[i]->setDeltaY(y());
            }*/
    }
    return arrp;
}

void PolylineItem::DeleteSelectNode()
{
    for (QGraphicsItem *itm: this->childItems()) {
        GrawItem *delItem = dynamic_cast<GrawItem*>(itm);
        if (delItem->isSelected()) {
            delete delItem;
        }
    }
    update();
}

void PolylineItem::InsertNode()
{
    for (QGraphicsItem *itm: this->childItems()) {
        GrawItem *insItem = dynamic_cast<GrawItem*>(itm);
        if (insItem->isSelected()) {
            //const int index = this->childItems().indexOf(insItem);

            GrawItem *newItem = ComponentFactory::createComponent(ComponentType::GraphNode);
            newItem->setParentItem(this);
            //const int indN = this->childItems().indexOf(newItem);

            newItem->setX(insItem->x()+5);
            newItem->setY(insItem->y()+5);
            //this->childItems().move(index+1, indN);
            //this->childItems().replace(index+1,newItem);

            connect(newItem, &GrawItem::signalParent, this, &GrawItem::isUpdateChild);
            break;
        }
    }
    update();
}
