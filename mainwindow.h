#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "components/componenttype.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringListModel>
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
    void setFileNameCommandLine(QString cFileNAme);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void onComponentTreeItemPressed(QTreeWidgetItem *item, int column);
    void onMouseLeftScene();
    void onMousePressed(const QPointF &point);
    void on_actionSvg_triggered();
    void on_tWProperty_cellDoubleClicked(int row, int column);

    void on_actSSPrint_triggered();

    void on_actSSReadOnly_triggered();

    void on_actSSNormal_triggered();

    void on_lvFiles_doubleClicked(const QModelIndex &index);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_actInsMakros_triggered();

    void on_actNewMakros_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_3_triggered();

private:
    void initScene();
    void makeConnections();
    void saveGraphFile(bool isMakros);
    void loadGraphFile();
    void fillTable() const;
    void fillFilesShems() const;
    void fillComponentLibrary() const;
    void setSceneState(SceneState sceneState);
    void addItemToTable(const GrawItem *item) const;
    void fillTblProp(const GrawItem *item) const;
    QString _FileNameJSC{""};
    QString _WindowsTitle{""};
    QStringListModel *model{nullptr};
    void CloneElement(const GrawItem *item);

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


