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
#include <QScrollBar>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillComponentLibrary();
    initScene();
    makeConnections();
    loadGraphFile();
    fillTable();
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

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->horizontalScrollBar()->setValue(1);
}

void MainWindow::saveGraphFile() const
{
    if (!listElem.isEmpty())
    {
        /*QFile file("Q_SXEMA");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        for (int i=0; i<listElem.count(); i++)
        {
            out << listElem[i]->x();
            out << listElem[i]->y();
            out << listElem[i]->id();
            out << listElem[i]->rotation();
        }
        file.close();*/

        QFile filejs("Q_SXEMA_JS.aqjs");
        filejs.open(QIODevice::WriteOnly);
        QJsonArray jsonArray;
        for (int i=0; i<listElem.count(); i++)
        {
            QJsonObject jsElement;
            jsElement.insert("X", listElem[i]->x());
            jsElement.insert("Y", listElem[i]->y());
            jsElement.insert("ID", listElem[i]->id());
            jsElement.insert("R", listElem[i]->rotation());
            jsonArray.append(jsElement);
        }
        QJsonDocument jsFile;
        jsFile.setArray(jsonArray);
        filejs.write(jsFile.toJson());
        filejs.close();
    }
}

void MainWindow::loadGraphFile()
{
    /*QFile file2("Q_SXEMA");
    file2.open(QIODevice::ReadOnly);
    QDataStream in(&file2);    // read the data serialized from the file

    qreal elposx;
    qreal elposy;
    int eltypeb;
    qreal elrotate;

    while (!in.atEnd())
    {
        in >> elposx;
        in >> elposy;
        in >> eltypeb;
        in >> elrotate;

        GrawItem *item = ComponentFactory::createComponent(eltypeb);
        if (!item)
            continue;

        listElem << item;
        scene->addItem(item);
        item->setPos(elposx, elposy);
        item->setRotation(elrotate);
    }
    file2.close();*/

    QFile filejs(QStringLiteral("Q_SXEMA_JS.aqjs"));
    filejs.open(QIODevice::ReadOnly);

    QByteArray saveData = filejs.readAll();
    QJsonDocument DocJs(QJsonDocument::fromJson(saveData));
    auto array = DocJs.array();
    for(const auto& json: array)
    {
      auto obj = json.toObject();
      GrawItem *item = ComponentFactory::createComponent(obj["ID"].toInt());
      if (!item)
          continue;

      listElem << item;
      scene->addItem(item);
      item->setPos(obj["X"].toInt(), obj["Y"].toInt());
      item->setRotation(obj["R"].toInt());

    }
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
    QTreeWidgetItem *category3TreeItem = new QTreeWidgetItem(ui->treeWidget);
    category3TreeItem->setText(columnIndex, "Categry Polyline");
    {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        treeItem->setText(columnIndex, "Polyline");
        treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Polyline));
        category3TreeItem->addChild(treeItem);
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

void MainWindow::onComponentTreeItemPressed(QTreeWidgetItem *item, int column)
{
    if (column != 0)
        return;

    const QVariant var = item->data(0, componentTypeRole);

    if (!var.isValid())
        return;

    qDebug() << var.toInt();

    const ComponentType selectedType = static_cast<ComponentType>(var.toInt());

    GrawItem *graw = ComponentFactory::createComponent(selectedType);
    if (!graw)
        return;

    setSceneState(SceneState::CreateComponentState);

    delete draftItem;
    draftItem = graw;
    draftItem->setFlag(QGraphicsItem::ItemIsMovable);
    //draftItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    //!!! Після цього нові елементи перестають привязуватись до сітки
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
    if (!newItem->IsVyzlElement() or !PolyItem) {
        newItem->setPos(point);
        scene->addItem(newItem);
        listElem.append(newItem);

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, new QTableWidgetItem((QString::number(newItem->x()))));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1, new QTableWidgetItem((QString::number(newItem->y()))));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(""));
        ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1,16);
    }

    if (newItem->IsVyzlElement()) {
        if (!PolyItem) {
            PolyItem=newItem;
        }else{
            PolyItem->AddNewVyzl(point);
        }
    }else{
        setSceneState(SceneState::NormalState); //Коли додано новий елемент то занулюємо статус
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << QKeySequence(event->key()).toString();
    if (event->key()== Qt::Key_Delete) {

        const QMessageBox::StandardButton resBtn = QMessageBox::question(this,
            "Паінтер", tr("Видалити виділені елементи?\n"), QMessageBox::No | QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes)
        {
            const QList<QGraphicsItem *> selectedItems = scene->selectedItems();
            for (QGraphicsItem *selectedItem : selectedItems)
            {
                // remove GrawItems only
                if (GrawItem *grawItem = dynamic_cast<GrawItem *>(selectedItem))
                {
                    const int index = listElem.indexOf(grawItem);
                    if (index != -1)
                    {
                        listElem.remove(index);
                        scene->removeItem(selectedItem);
                        ui->tableWidget->removeRow(index);
                    }
                }
            }
        }
    }

    if  (event->key()== Qt::Key_Escape) {
        MainWindow::onMouseLeftScene();
    }

    if (event->key()== Qt::Key_R) {
        const QList<QGraphicsItem *> selectedItems = scene->selectedItems();
        for (QGraphicsItem *selectedItem : selectedItems)
        {
            if (GrawItem *grawItem = dynamic_cast<GrawItem *>(selectedItem))
            {
                grawItem->RotateFlip();
            }
        }
    }
}
