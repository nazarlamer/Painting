#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView: public QGraphicsView
{

public:
    explicit MyGraphicsView(QWidget *parent);
    ~MyGraphicsView();

private:
    bool rightMousePressed;
    int _panStartX;
    int _panStartY;


protected:
    virtual void wheelEvent(QWheelEvent *event);

protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MYGRAPHICSVIEW_H
