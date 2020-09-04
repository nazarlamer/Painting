#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicsscene.h"
#include "components/grawitem.h"
#include "components/componentfactory.h"

#include <QDebug>
#include <QTableWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QVariant>
#include <QGraphicsSceneMouseEvent>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillComponentLibrary();
    initScene();
    makeConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete draftItem;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (state == SceneState::NormalState)
        return false;

    if (watched != scene)
        return false;

    if (event->type() == QEvent::GraphicsSceneContextMenu)
    {
        setSceneState(SceneState::NormalState);
        return true;
    }

    if (event->type() == QEvent::Enter && state == SceneState::CreateComponentState && draftItem)
        scene->addItem(draftItem);

    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        auto mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        const auto mousePos = mouseEvent->scenePos();

        if (state == SceneState::CreateComponentState && draftItem)
        {
            const auto areaCenter = draftItem->boundingRect().center();
            draftItem->setPos({ mousePos.x() - areaCenter.x(), mousePos.y() - areaCenter.y() });
        }
        return false;
    }

    return false;
}

void MainWindow::initScene()
{
    scene = new MyGraphicsScene(this);
    scene->setSceneRect(0, 0, 20000, 20000);
    scene->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
}

void MainWindow::saveGraphFile() const
{
    if (!listElem.isEmpty())
    {
        QFile file("Q_SXEMA");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        for (int i=0; i<listElem.count(); i++)
        {
            out << listElem[i]->x();
            out << listElem[i]->y();
            out << listElem[i]->id();
        }

        file.close();
    }
}

void MainWindow::loadGraphFile()
{
    QFile file2("Q_SXEMA");
    file2.open(QIODevice::ReadOnly);
    QDataStream in(&file2);    // read the data serialized from the file
    qreal elposx;
    qreal elposy;
    int eltypeb;
    while (!in.atEnd())
    {
        in >> elposx;
        in >> elposy;
        in >> eltypeb;

        GrawItem *item = ComponentFactory::createComponent(eltypeb);
        if (!item)
            continue;

        listElem << item;
        scene->addItem(item);
        item->setPos(elposx, elposy);
    }
    file2.close();
}

void MainWindow::fillTable() const
{
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"POSX", "POSY","SEL"});

    int InsR = 0;
    for (int i=0; i<listElem.size(); ++i)
    {
        const GrawItem *graw = listElem[i];
        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(graw->x()))));
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(graw->y()))));
        ui->tableWidget->setItem(InsR,2, new QTableWidgetItem(""));
        ui->tableWidget->setRowHeight(InsR,16);
        InsR += 1;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::fillComponentLibrary() const
{
    const int columnIndex = 0;

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setAlternatingRowColors(true);

    QTreeWidgetItem *category1TreeItem = new QTreeWidgetItem(ui->treeWidget);
    category1TreeItem->setText(columnIndex, "Categry 1");
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        treeItem->setText(columnIndex, "Line");
        treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Line));
        category1TreeItem->addChild(treeItem);
    }
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        treeItem->setText(columnIndex, "Arrow");
        treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Arrow));
        category1TreeItem->addChild(treeItem);
    }

    QTreeWidgetItem *category2TreeItem = new QTreeWidgetItem(ui->treeWidget);
    category2TreeItem->setText(columnIndex, "Categry 2");
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        treeItem->setText(columnIndex, "Circle");
        treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Circle));
        category2TreeItem->addChild(treeItem);
    }
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        treeItem->setText(columnIndex, "Rectangle");
        treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Rectangle));
        category2TreeItem->addChild(treeItem);
    }
}

void MainWindow::setSceneState(SceneState sceneState)
{
    state = sceneState;

    if (state == SceneState::NormalState)
    {
        delete draftItem;
        draftItem = nullptr;
    }
}

void MainWindow::makeConnections()
{
    connect(ui->addLineAction, &QAction::triggered, this, &MainWindow::onAddLineActionTriggered);
    connect(ui->addArrowAction, &QAction::triggered, this, &MainWindow::onAddArrowActionTriggered);
    connect(ui->addCircleAction, &QAction::triggered, this, &MainWindow::onAddCircleActionTriggered);
    connect(ui->addRectangleAction, &QAction::triggered, this, &MainWindow::onAddRectangleActionTriggered);
    connect(ui->treeWidget, &QTreeWidget::itemPressed, this, &MainWindow::onComponentTreeItemPressed);
    connect(scene, &MyGraphicsScene::mouseLeftScene, this, &MainWindow::onMouseLeftScene);
    connect(scene, &MyGraphicsScene::leftButtonMousePress, this, &MainWindow::onMousePressed);
}

void MainWindow::closeEvent(QCloseEvent *bar){
    saveGraphFile();
    //bar->accept();
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,
        "Паінтер", tr("Завершити роботу програми?\n"), QMessageBox::No | QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes) {
        bar->ignore();
    } else {
        bar->accept();
    }
}

void MainWindow::onAddLineActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Line);
    if (!graw)
        return;

    listElem << graw;
    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddArrowActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Arrow);
    if (!graw)
        return;

    listElem << graw;
    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddCircleActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Circle);
    if (!graw)
        return;

    listElem << graw;
    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddRectangleActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Rectangle);
    if (!graw)
        return;

    listElem << graw;
    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onComponentTreeItemPressed(QTreeWidgetItem *item, int column)
{
    if (column != 0)
        return;

    const QVariant var = item->data(0, componentTypeRole);
    if (!var.isValid())
        return;

    const ComponentType selectedType = static_cast<ComponentType>(var.toInt());
    GrawItem *graw = ComponentFactory::createComponent(selectedType);
    if (!graw)
        return;

    setSceneState(SceneState::CreateComponentState);

    delete draftItem;
    draftItem = graw;
    draftItem->setFlag(QGraphicsItem::ItemIsMovable);
    draftItem->setZValue(0);
}

void MainWindow::onMouseLeftScene()
{
    if (draftItem)
        scene->removeItem(draftItem);
}

void MainWindow::onMousePressed(const QPointF &point)
{
    if (state != SceneState::CreateComponentState)
    {
        for (int i=0; i<listElem.size(); ++i)
        {
            const GrawItem *grawsel = listElem[i];
            if (grawsel->isSelected()) {
                ui->tableWidget->selectRow(i);
                return;
            }
        }
        return;
    }

    if (!draftItem)
        return;

    GrawItem *newItem = ComponentFactory::createComponent(draftItem->componentType());
    //newItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable); ??? Цього не потрібно робити, ботім доданий елемент переміщається разом з іншим
    newItem->setPos(point);
    scene->addItem(newItem);
    listElem.append(newItem);

    setSceneState(SceneState::NormalState); //Коли додано новий елемент то занулюємо статус
}

void MainWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if (!IsLoad) {
        ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        ui->graphicsView->setScene(scene);

        loadGraphFile();
        fillTable();
        IsLoad = true;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    //qDebug() << QKeySequence(event->key()).toString();
    if (event->key()== Qt::Key_Delete) {

        QMessageBox::StandardButton resBtn = QMessageBox::question(this,
            "Паінтер", tr("Видалити активний елемент?\n"), QMessageBox::No | QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes) {
            //bar->ignore();
        } else {
            //bar->accept();
        }
    }
}
