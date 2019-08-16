#include <QDebug>
#include <QPainter>
#include <QPicture>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

#include <iostream>
#include <fstream>

#include <QWidget>
#include <QTableWidgetItem>
#include <QFile>

#include<QMessageBox>
#include<QCloseEvent>
#include<QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();

    /*scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    rectangle = scene->addRect(0, 0, 80, 100, outlinePen, blueBrush);

    // addEllipse(x,y,w,h,pen,brush)
    ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);

    text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
    // movable text
    text->setFlag(QGraphicsItem::ItemIsMovable);
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
    //ui->scrollAreaWidgetContents->setLayout(ui->graphicsView);*/

    QPainter painterl;
    QPainter painter2;

    painterl.begin(this);
    painterl.end();


    painter2.begin(this);
    painter2. end () ;



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

/*void graphicsView::paintEvent(QPaintEvent *event)
{
    static int count = 0;
    qDebug("paintEvent, %d", count++);
}

        QPainter painter(this);
        painter.begin(this);
        QRect rect(10,10,100,100);

        QPen pen(Qt::red);
        pen.setWidth(5);

        painter.setPen(pen);
        painter.drawRect(rect);
        painter.end();
 */


void MainWindow::on_pushButton_clicked()
{
    //QBrush bru(Qt::BrushStyle::VerPattern);
    //scene->setForegroundBrush(bru);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);

    //scene->addLine(0,0,100,100);

    rectangle = scene->addRect(0,0,100,100);
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);

    /*
    graws = new Graws(1);
    graws->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graws;

    scene->addItem(graws);
    graws->setPos(50,50);

    graws = new Graws(2);
    graws->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graws;

    scene->addItem(graws);
    graws->setPos(100,100);
    */

    QFile file2("Q_SXEMA");
    file2.open(QIODevice::ReadOnly);
    QDataStream in(&file2);    // read the data serialized from the file
    qreal elposx;
    qreal elposy;
    int eltypeb;
    while (!in.atEnd()) {
        in >> elposx;
        in >> elposy;
        in >> eltypeb;

        graws = new Graws(eltypeb);
        graws->setFlag(QGraphicsItem::ItemIsMovable);
        listElem << graws;
        scene->addItem(graws);
        graws->setPos(elposx, elposy);
    }
    file2.close();


    /*
    fstream inFile;
    int posx;
    int posy;
    int buffer[2] = {0};
    int typeob = 0;
    inFile.open("SXEMA", ios::binary | ios::in);

    inFile.seekg(0);
    while(!inFile.eof())
    {
        inFile.read(reinterpret_cast<char*>(buffer), sizeof(int)*2);
        posx =buffer[0];
        posy =buffer[1];
        inFile.read(reinterpret_cast<char*>(typeob), sizeof(int));

        graws = new Graws(typeob);
        graws->setFlag(QGraphicsItem::ItemIsMovable);
        listElem << graws;

        scene->addItem(graws);
        graws->setPos(posx,posy);
    }
    inFile.close();
    */

    //ui->graphicsView->a
    //scene->addItem(painter);
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"POSX", "POSY"});

    int InsR = 0;
    listElem.first();
    for (int i=0; i<listElem.count(); i++) {
        graws = listElem[i];
        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(graws->x()))));
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(graws->y()))));
        ui->tableWidget->setRowHeight(InsR,16);
    InsR += 1;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::on_pushButton_2_clicked()
{


}

void MainWindow::on_MainWindow_destroyed()
{
    SaveGraphFile();
}

void MainWindow::SaveGraphFile()
{
    /*std::fstream inFile;
    inFile.open("SXEMA", std::ios::binary | std::ios::out);

    if (not listElem.isEmpty()) {
        listElem.first();
        for (int i=0; i<listElem.count(); i++) {
            graws = listElem[i];
            inFile << (int) graws->x();
            inFile << (int) graws->y();
            inFile << graws->idelem;
        }
        inFile.close();
    }*/

    /*
    QFile fileOut("Q_SXEMA");
    fileOut.open(QIODevice::WriteOnly);
    qreal f=100;
    QByteArray block(reinterpret_cast<const char*>(&f), sizeof(f));
    fileOut.write(block);
    fileOut.close(); // Закрываем fileout.txt


    QFile filein("Q_SXEMA");
    filein.open(QIODevice::ReadOnly);
    qreal fin;
    QByteArray blockin = filein.read(sizeof(fin));
    QDataStream streamOut(blockin);
    streamOut >> fin;
    filein.close(); // Закрываем fileout.txt
    */

    if (!listElem.isEmpty()) {
        QFile file("Q_SXEMA");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        listElem.first();
        for (int i=0; i<listElem.count(); i++) {
            graws = listElem[i];
            out << graws->x();
            out << graws->y();
            out << graws->idelem;
        }

        file.close();
    }

    /*
    QFile file2("Q_SXEMA");
    file2.open(QIODevice::ReadOnly);
    QDataStream in(&file2);    // read the data serialized from the file
    qreal a;
    int b;
    while (!in.atEnd()) {
    in >> a;           // extract "the answer is" and 42
    qDebug() << a;
    in >> a;           // extract "the answer is" and 42
    qDebug() << a;
    in >> b;
    qDebug() << b;
    }
    file2.close();
    */

    /*
    QFile fileIn("filein.txt");
    QFile fileOut("fileout.txt");
    if(fileIn.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly))
    { //Если первый файл открыт для чтения, а второй для записи успешн
        QByteArray block = fileIn.read(10); // Считываем 10 байт в массив block из filein.txt
        fileOut.write(block); // Записываем 10 байт в файл fileout.txt
        fileIn.close(); // Закрываем filein.txt
        fileOut.close(); // Закрываем fileout.txt
    }
    */

}

void MainWindow::on_pushButton_3_clicked()
{
    SaveGraphFile();
}

void MainWindow::closeEvent(QCloseEvent *bar){
    SaveGraphFile();
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

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_action_triggered()
{
    /*
    QPicture picDAT;
    QPainter painter;
    painter.begin(&picDAT);
    painter.drawLine(20, 20, 50, 50);
    painter.end();
    picDAT.save("D:\\TestObj.dat");
    */
    graws = new Graws(3);
    graws->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graws;

    scene->addItem(graws);
    graws->setPos(100,100);
}

void MainWindow::on_action_5_triggered()
{
    graws = new Graws(2);
    graws->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graws;

    scene->addItem(graws);
    graws->setPos(100,100);
}

void MainWindow::on_action_6_triggered()
{
    graws = new Graws(4);
    graws->setFlag(QGraphicsItem::ItemIsMovable);
    listElem << graws;

    scene->addItem(graws);
    graws->setPos(100,100);
}
