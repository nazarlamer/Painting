#ifndef MYGRAFICVIEW_H
#define MYGRAFICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

class mygraficview: public QGraphicsView
{
    Q_OBJECT
public:
    explicit mygraficview(QWidget *parent = nullptr);

protected slots:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MYGRAFICVIEW_H
