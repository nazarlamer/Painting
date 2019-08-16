#include "mygraphicsview.h"
#include <QKeyEvent>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent): QGraphicsView(parent)
{
    //setDragMode(QGraphicsView::ScrollHandDrag);
}

MyGraphicsView::~MyGraphicsView()
{

}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        setDragMode(QGraphicsView::ScrollHandDrag);

        //    rightMousePressed = true;
        //    _panStartX = event->x();
        //    _panStartY = event->y();
        //    setCursor(Qt::ClosedHandCursor);
        //    event->accept();
        //    return;
        //}
        //qDebug() << "mousePressEvent";
        //return;
    }

    //if (event->button() == Qt::LeftButton) {

    //}


    // передаём остальные кнопки в базовый класс
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "mouseReleaseEvent";
    /*
    if (event->button() == Qt::LeftButton) {

    }
    */

    if (event->button() == Qt::LeftButton)
    {
        setDragMode(QGraphicsView::NoDrag);
        //    rightMousePressed = false;
        //    setCursor(Qt::ArrowCursor);
        //    event->accept();
        //    return;
    }
    //event->ignore();

    // передаём остальные кнопки в базовый класс
    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){

    //if (rightMousePressed)
    //{
        //qDebug() << event->x() << " " <<event->y();
        //this->horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        //this->verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        //_panStartX = event->x();
        //_panStartY = event->y();
        //event->accept();

        //QPointF oldp = mapToScene(_panStartX, _panStartY);
        //QPointF newP = event->pos();
        //QPointF translation = newP;
        //QPointF translation = newP - oldp;

         //translate(translation.x(), translation.y());

         //_panStartX = event->x();
         //_panStartY = event->y();

        //return;
    //}
    //event->ignore();

    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;

    if(event->delta() > 0)
        {
            scale(scaleFactor, scaleFactor);
        }
        else
        {
            scale(1/scaleFactor, 1/scaleFactor);
        }
}
