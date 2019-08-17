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

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();
    makeConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene()
{
    scene = new MyGraphicsScene(this);
    scene->setSceneRect(0, 0, 20000, 20000);
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

        item->setFlag(QGraphicsItem::ItemIsMovable);
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
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"POSX", "POSY"});

    int InsR = 0;
    for (int i=0; i<listElem.size(); ++i)
    {
        const GrawItem *graw = listElem[i];
        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(graw->x()))));
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(graw->y()))));
        ui->tableWidget->setRowHeight(InsR,16);
    InsR += 1;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::makeConnections()
{
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->addLineAction, &QAction::triggered, this, &MainWindow::onAddLineActionTriggered);
    connect(ui->addArrowAction, &QAction::triggered, this, &MainWindow::onAddArrowActionTriggered);
    connect(ui->addCircleAction, &QAction::triggered, this, &MainWindow::onAddCircleActionTriggered);
    connect(ui->addRectangleAction, &QAction::triggered,
            this, &MainWindow::onAddRectangleActionTriggered);
}

void MainWindow::onOpenButtonClicked()
{
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);

    loadGraphFile();
    fillTable();
}

void MainWindow::closeEvent(QCloseEvent *bar){
    saveGraphFile();
    //bar->accept();
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        bar->ignore();
    } else {
        bar->accept();
    }
}

void MainWindow::on_action_triggered()
{
    GrawItem *graw = ComponentFactory::createComponent(3);
    graw->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graw;

    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddLineActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Line);
    if (!graw)
        return;

    graw->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graw;

    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddArrowActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Arrow);
    if (!graw)
        return;

    graw->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graw;

    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddCircleActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Circle);
    if (!graw)
        return;

    graw->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graw;

    scene->addItem(graw);
    graw->setPos(100,100);
}

void MainWindow::onAddRectangleActionTriggered()
{
    GrawItem *graw = ComponentFactory::createComponent(ComponentType::Rectangle);
    if (!graw)
        return;

    graw->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graw;

    scene->addItem(graw);
    graw->setPos(100,100);
}
