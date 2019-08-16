#ifndef GRAWS_H
#define GRAWS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>


class Graws: public QGraphicsItem
{

    Q_PROPERTY(int id_el READ idelem WRITE idelem)

public:
    Graws(int IDElem);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    int idelem;

protected:
    QRectF boundingRect() const;    /* We define a virtual method that returns the area in which the triangle is
                                     * */
    /* Define a method for rendering a triangle
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // GRAWS_H
