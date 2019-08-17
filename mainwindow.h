#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AbstractGraw;
class MyGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onOpenButtonClicked();

    void on_action_triggered();
    void on_action_5_triggered();
    void on_action_6_triggered();

private:
    void initScene();
    void makeConnections();
    void saveGraphFile() const;
    void loadGraphFile();
    void fillTable() const;

private:
    Ui::MainWindow *ui{nullptr};
    MyGraphicsScene *scene{nullptr};

    // do not use concreate objects - use abstract objects like QGraphicsItem or some other abstract
    // class (DELETE THIS COMMENT AFTER READ)
    QList<AbstractGraw*> listElem;
};

#endif // MAINWINDOW_H


