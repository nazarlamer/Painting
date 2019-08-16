#include "graws.h"
#include <math.h>
#include <QPicture>

Graws::Graws(int IDElem):
    QGraphicsItem()
{
    setFlags(//QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);

    idelem = IDElem;
}


/*
Graws::Graws(const QRect& rect, QGraphicsItem* parent,
                               QGraphicsScene* scene):
    QGraphicsItem(rect, parent, scene)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
}
*/

QRectF Graws::boundingRect() const
{
    switch  (idelem)
    {
        case 1:
            return QRectF(-20, -20, 40, 40);

        case 2:
            return QRectF(-10, -10, 20, 20);

        case 3:
            return QRectF(0, 0, 20, 50);

        case 4:
            return QRectF(-20, -20, 40, 40);

        default:
            return QRectF(-25, -40, 50, 80);
    }
       // We are limiting the area of triangle
}

void Graws::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if (idelem==1) {
        //QPen pen(QColor("#0e5a77"), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //QBrush greyBrush(QColor(212,175,55), Qt::NoBrush);

        /*pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setBrush(Qt::red);
        painter->setPen(pen2);*/

        //painter->setPen(Qt::red);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(-20, -20, 40, 40));

        /*pen2.setStyle(Qt::SolidLine);
        pen2.setWidth(3);
        pen2.setBrush(Qt::green);
        pen2.setCapStyle(Qt::RoundCap);
        pen2.setJoinStyle(Qt::RoundJoin);*/
        //QPen pen2(QColor("#0e5a77"), 5, Qt::DotLine, Qt::FlatCap, Qt::RoundJoin);
        //QBrush greyBrush2(QColor(212,175,55), Qt::SolidPattern);

        //painter->drawRect(QRect(-20, -20, 40, 40));
        //painter->setBrush(Qt::yellow);


        painter->setPen(QPen(Qt::red, 3));
        painter->setBrush(Qt::SolidPattern);
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(QRect(-20, -20, 40, 40));


        Q_UNUSED(option);
        Q_UNUSED(widget);

        return;
    }


    if (idelem==2) {
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(-10, -10, 20, 20));

        painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
        painter->drawLine(0, -8, 0, 8);

        //QTransform t;
        //t.rotate(90);
        setRotation(90);

        Q_UNUSED(option);
        Q_UNUSED(widget);

        return;
    }

    if (idelem==3) {
        QString ttt("50, 20");
        painter->drawRect(QRect(0, 0, 20, 50));
        painter->drawText(boundingRect(), Qt::AlignCenter, ttt);
        return;
    }

    if (idelem==4) {
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(-20, -20, 40, 40));

        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        QVector<QPoint> linemufta;
        linemufta << QPoint(-15, -10) << QPoint(15,-10) << QPoint(0,6);
        painter->drawPolygon(linemufta);

        painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
        painter->drawLine(0, -11, 0, -18);
        painter->drawLine(0, 10, 0, 18);
        return;
    }

    QRect rect(-25,-40,50,80);
    painter->setBrush(Qt::yellow);
    painter->drawRect(rect);
    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
    polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
    painter->setBrush(Qt::red);     // We set the brush, which will render the object
    painter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
    QRect rect2(0,0,10,10);
    painter->drawRect(rect2);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


QVariant Graws::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //qDebug() << "itemChange";
    if (change == ItemPositionChange && scene()) {
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

/*
QVariant Graws::itemChange(GraphicsItemChange change,
const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<Scene*> (scene())){
            Scene* customScene = qobject_cast<Scene*> (scene());
            int gridSize = customScene->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}
*/
