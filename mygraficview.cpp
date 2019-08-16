#include "mygraficview.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QDebug>



void mygraficview::mousePressEvent(QMouseEvent *event)
{
        QGraphicsView::mousePressEvent(event);  // З
        qDebug() << "Pressed";
}
