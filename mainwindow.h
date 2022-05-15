#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "components/componenttype.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "scenestates.h"

class GrawItem;
class MyGraphicsScene;
class QTreeWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onComponentTreeItemPressed(QTreeWidgetItem *item, int column);
    void onMouseLeftScene();
    void onMousePressed(const QPointF &point);

    void on_action_3_triggered();
    void on_actionSvg_changed();
    void on_actionSvg_triggered();

    void on_tWProperty_cellDoubleClicked(int row, int column);

private:
    void initScene();
    void makeConnections();
    void saveGraphFile() const;
    void loadGraphFile();
    void fillTable() const;
    void fillComponentLibrary() const;
    void setSceneState(SceneState sceneState);
    void addItemToTable(const GrawItem *item) const;

private:
    Ui::MainWindow *ui{nullptr};
    MyGraphicsScene *scene{nullptr};
    SceneState state{SceneState::NormalState};
    ComponentType selectedComponentType{ComponentType::None};

    QVector<GrawItem*> listElem;
    GrawItem *draftItem{nullptr};
    GrawItem *PolyItem{nullptr}; //для додавання вузлових елементів
    const int componentTypeRole{Qt::UserRole + 1};
};

#endif // MAINWINDOW_H


