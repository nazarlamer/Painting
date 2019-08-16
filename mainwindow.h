#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <graws.h>
#include <mygraphicsscene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsItem *SelectGrItem;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_MainWindow_destroyed();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_action_triggered();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

private:
    Ui::MainWindow *ui;

    //QGraphicsScene *scene;
    MyGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    Graws *graws;
    QList<Graws*> listElem;

    void SaveGraphFile();
    void closeEvent(QCloseEvent *bar);
};

#endif // MAINWINDOW_H


