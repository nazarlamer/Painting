#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GrawItem;
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
    void onAddLineActionTriggered();
    void onAddArrowActionTriggered();
    void onAddCircleActionTriggered();
    void onAddRectangleActionTriggered();

    void on_action_triggered();

private:
    void initScene();
    void makeConnections();
    void saveGraphFile() const;
    void loadGraphFile();
    void fillTable() const;
    void fillComponentLibrary() const;

private:
    Ui::MainWindow *ui{nullptr};
    MyGraphicsScene *scene{nullptr};

    // do not use concreate objects - use abstract objects like QGraphicsItem or some other abstract
    // class (DELETE THIS COMMENT AFTER READ)
    QList<GrawItem*> listElem;
    const int componentTypeRole{Qt::UserRole + 1};
};

#endif // MAINWINDOW_H


