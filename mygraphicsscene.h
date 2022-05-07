#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

class MyGraphicsScene: public QGraphicsScene
{
    Q_OBJECT
public:
    MyGraphicsScene(QObject *parent);
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);

signals:
    void mouseLeftScene();
    void leftButtonMousePress(const QPointF &point);

    // QGraphicsScene interface
 protected:
   void drawBackground(QPainter * painter, const QRectF & rect ) override;
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

   // QObject interface
public:
   bool event(QEvent *event) override;
   void setSceneMouseEnent(bool ievent);

private:
   bool MouseEvent;

};

#endif // MYGRAPHICSSCENE_H
