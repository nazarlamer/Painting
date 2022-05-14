#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "scenestates.h"

class MyGraphicsScene: public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicsScene(QObject *parent);
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);
    void setSceneState(SceneState iscenestate);

public slots:
    void UpdateScen();

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
    SceneState _scenestate{SceneState::NormalState};

};

#endif // MYGRAPHICSSCENE_H
