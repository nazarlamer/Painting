#include "graws.h"

#include <cmath> // use cmath but do not use math.h
#include <QPicture>
#include <QPainter>

QRectF Graws::boundingRect() const
{
//    switch  (idElem)
//    {
//    case 1:
//        return QRectF(-20, -20, 40, 40);
//    case 2:
//        return QRectF(-10, -10, 20, 20);
//    case 3:
//        return QRectF(0, 0, 20, 50);
//    case 4:
//        return QRectF(-20, -20, 40, 40);
//    default:
//        return QRectF(-25, -40, 50, 80);
//    }
       // We are limiting the area of triangle

    return {};
}

void Graws::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    if (idElem==1)
//    {
//        //QPen pen(QColor("#0e5a77"), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        //QBrush greyBrush(QColor(212,175,55), Qt::NoBrush);

//        /*pen.setStyle(Qt::SolidLine);
//        pen.setWidth(1);
//        pen.setBrush(Qt::red);
//        painter->setPen(pen2);*/

//        //painter->setPen(Qt::red);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(Qt::NoBrush);
//        painter->drawRect(QRect(-20, -20, 40, 40));

//        /*pen2.setStyle(Qt::SolidLine);
//        pen2.setWidth(3);
//        pen2.setBrush(Qt::green);
//        pen2.setCapStyle(Qt::RoundCap);
//        pen2.setJoinStyle(Qt::RoundJoin);*/
//        //QPen pen2(QColor("#0e5a77"), 5, Qt::DotLine, Qt::FlatCap, Qt::RoundJoin);
//        //QBrush greyBrush2(QColor(212,175,55), Qt::SolidPattern);

//        //painter->drawRect(QRect(-20, -20, 40, 40));
//        //painter->setBrush(Qt::yellow);

//        painter->setPen(QPen(Qt::red, 3));
//        painter->setBrush(Qt::SolidPattern);
//        painter->setBrush(Qt::yellow);
//        painter->drawEllipse(QRect(-20, -20, 40, 40));

//        return;
//    }

//    if (idElem==3)
//    {
//        QString ttt("50, 20");
//        painter->drawRect(QRect(0, 0, 20, 50));
//        painter->drawText(boundingRect(), Qt::AlignCenter, ttt);
//        return;
//    }

//    QRect rect(-25,-40,50,80);
//    painter->setBrush(Qt::yellow);
//    painter->drawRect(rect);
//    QPolygon polygon;   // Using Polygon class, to draw the triangle
//    // We put the coordinates of points in the polygonal model
//    polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
//    painter->setBrush(Qt::red);     // We set the brush, which will render the object
//    painter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
//    QRect rect2(0,0,10,10);
//    painter->drawRect(rect2);
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
