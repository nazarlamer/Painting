#include "mygraphicsscene.h"
#include <math.h>
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>


MyGraphicsScene::MyGraphicsScene(QObject *parent): QGraphicsScene (parent)
{
    qDebug() << "MyGraphicsScene";
}

void MyGraphicsScene::setSceneRect(qreal x, qreal y, qreal w, qreal h) {
    QGraphicsScene::setSceneRect(x, y, w, h);
    //qDebug() << "setSceneRect";
    //this->addLine(50,50,0,50);

    /*
    QRect rect(-1, -1, 2, 2);
    for (int i=0; i<(w/10); i++)
    {
        for (int j=0; j<(h/10); j++)
        {
            //QRect rect((i*10)-2, (j*10)-2, (i*10)+2, (j*10)+2);
            //QRect rect((i*10)-1, (j*10)-1, 2, 2);
            rect.setX((i*10)-1);
            rect.setY((j*10)-1);
            rect.setWidth(2);
            rect.setHeight(2);
            this->addRect(rect, QPen(QColor("#888888")), QBrush(QColor("#888888")));
        }
    }
    */
}

void MyGraphicsScene::setSceneState(SceneState iscenestate)
{
    _scenestate = iscenestate;
    update();
}

void MyGraphicsScene::UpdateScen()
{
    qDebug() << "MyGraphicsScene :: UpdateScen";
    update();
}

static const int GRID_STEP = 30;

void MyGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
   //qDebug() << rect.x();
   /*
   int step = GRID_STEP;
   painter->setPen(QPen(QColor(200, 200, 255, 125)));
   // draw horizontal grid
   qreal start = round(rect.top()/step);
   if (start > rect.top()) {
      start -= step;
   }
   for (qreal y = start - step; y < rect.bottom(); ) {
      y += step;
      painter->drawLine(rect.left(), y, rect.right(), y);
   }
   // now draw vertical grid
   start = round(rect.left()/step);
   if (start > rect.left()) {
      start -= step;
   }
   for (qreal x = start - step; x < rect.right(); ) {
      x += step;
      painter->drawLine(x, rect.top(), x, rect.bottom());
   }
   */

    painter->save();

    if (_scenestate == SceneState::PrintState)
        painter->fillRect(rect, QColor(255, 255, 255, 255));
    else
        painter->fillRect(rect, QColor(255, 237, 176, 255));

    if (_scenestate!=SceneState::SaveSvgFile and _scenestate!=SceneState::ReadOnlyState and _scenestate!=SceneState::PrintState) {

        const QRectF rectp = rect.normalized();
        painter->setPen(QPen(Qt::lightGray,1));
        int l = int(rectp.left());
        l -= (l % 10);

        int r = int(rectp.right());
        r -= (r % 10);
        if(r < int(rectp.right()))
        r += 10;

        int t = int(rectp.top());
        t -= (t % 10);

        int b = int(rectp.bottom());
        b -= (b % 10);
        if(b < int(rectp.bottom()))
           b += 10;

        for( int x = l; x <= r; x+=10)
           for( int y = t; y <= b; y+=10)
              painter->drawPoint(x, y);
    }

    painter->restore();

   /*
   const int gridSize = 10;
   qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
   qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
   QVarLengthArray<QLineF, 100> lines;
   for (qreal x = left; x < rect.right(); x += gridSize)
       lines.append(QLineF(x, rect.top(), x, rect.bottom()));
   for (qreal y = top; y < rect.bottom(); y += gridSize)
       lines.append(QLineF(rect.left(), y, rect.right(), y));
   qDebug() << lines.size();
   painter->drawLines(lines.data(), lines.size());
   */

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
        emit leftButtonMousePress(event->scenePos());
}

bool MyGraphicsScene::event(QEvent *event)
{
    if (event->type() == QEvent::Leave)
        emit mouseLeftScene();

    return QGraphicsScene::event(event);
}
