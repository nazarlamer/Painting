#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

class MyGraphicsScene: public QGraphicsScene
{

public:
    MyGraphicsScene(QObject *parent);
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);

protected:
   void drawBackground(QPainter * painter, const QRectF & rect );

};

#endif // MYGRAPHICSSCENE_H
