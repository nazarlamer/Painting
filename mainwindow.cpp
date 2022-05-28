/*Стабільний коміт 23.05.2022*/
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
#include <QInputDialog>
#include <QColorDialog>
#include <QStringListModel>
#include <QUuid>

#include <QSvgGenerator>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillComponentLibrary();
    initScene();
    makeConnections();

    //_FileNameJSC = "Q_SXEMA_JS.aqjs";
    //loadGraphFile();

    model = new QStringListModel(this);
    fillFilesShems();

    // Разрешаем выделение только одного элемента
    ui->tWProperty->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tWProperty->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tWProperty->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tWProperty->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tWProperty->setVisible(false);
    ui->tableWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete draftItem;
    _WindowsTitle = this->windowTitle();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (state == SceneState::NormalState)
        return false;

    if (watched != scene)
        return false;

    if (event->type() == QEvent::GraphicsSceneContextMenu)
    {
        if (PolyItem){
            //delete PolyItem; // це видаляє обєкт, не можна, тільки посилання
            PolyItem=nullptr;
        }

        setSceneState(SceneState::NormalState);
        return true;
    }

    if (event->type() == QEvent::Enter && state == SceneState::CreateComponentState && draftItem)
        scene->addItem(draftItem);

    //переміщення мишки
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

void MainWindow::saveGraphFile(bool isMakros=false)
{
    if (!listElem.isEmpty())
    {
        QString PNameFile;
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

        if (_FileNameJSC=="") {
            QString str = QUuid::createUuid().toString();
            _FileNameJSC = str + ".aqjs";
            this->setWindowTitle(_WindowsTitle+"["+_FileNameJSC+"]");
        }

        if (isMakros) {
            PNameFile = _FileNameJSC;
            QString str = QUuid::createUuid().toString();
            _FileNameJSC = "makros\\" + str + ".mkjs";
        }

        QFile filejs(_FileNameJSC);
        filejs.open(QIODevice::WriteOnly);
        QJsonArray jsonArray;
        for (int i=0; i<listElem.count(); i++)
        {
            if (listElem[i]->componentType() == ComponentType::GraphNode)
                continue;

            if (listElem[i]->IsNodesElement() and listElem[i]->GetPoints().count()==0)
                continue;

            QJsonObject jsElement;
            jsElement.insert("X", listElem[i]->x());
            jsElement.insert("Y", listElem[i]->y());
            jsElement.insert("ID", listElem[i]->id());
            jsElement.insert("R", listElem[i]->rotation());
            jsElement.insert("W", listElem[i]->boundingRect().width());
            jsElement.insert("H", listElem[i]->boundingRect().height());
            jsElement.insert("Z", listElem[i]->zValue());

            QJsonArray jsArrProperty;

            QList<QPair<QString, QString>> listProp = listElem[i]->getListPropText();
            if (listProp.count()>0) {
                for (int k=0; k<listProp.count(); k++) {
                    QVariant varProp = listElem[i]->getPropVariant(listProp.at(k).first);
                    if (varProp.isNull())
                        continue;
                    QJsonObject jsProperty;
                    jsProperty.insert(listProp[k].first, QJsonValue::fromVariant(varProp));
                    jsArrProperty.append(jsProperty);
                }
            }

            jsElement.insert("PROPERTY", jsArrProperty);

            if (listElem[i]->IsNodesElement()) {
                QJsonArray NodesArray;
                for (int k=0; k<listElem[i]->GetPoints().count(); k++) {
                    GrawItem *grawvyzol = listElem[i]->GetPoints()[k];
                    QJsonArray NodeArray;
                    NodeArray.append(grawvyzol->x());
                    NodeArray.append(grawvyzol->y());
                    NodesArray.append(NodeArray);
                }
                jsElement.insert("NODES", NodesArray);
            }

            if (listElem[i]->componentType() == ComponentType::SvgItem) {
                jsElement.insert("CONTENT", listElem[i]->getByteArrCont().data());
            }

            jsonArray.append(jsElement);

            if (isMakros) {
                QJsonObject jsElement;
                jsElement.insert("NAME", "");
                jsElement.insert("ID", -2);
                jsonArray.append(jsElement);
            }

        }
        QJsonDocument jsFile;
        jsFile.setArray(jsonArray);
        filejs.write(jsFile.toJson());
        filejs.close();

        if (isMakros) {
            _FileNameJSC = PNameFile;
        }
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

    scene->clear();
    listElem.clear();

    QFile filejs(_FileNameJSC);
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

        item->setPos(obj["X"].toInt(), obj["Y"].toInt());
        item->setRotation(obj["R"].toInt());
        item->setZValue(obj["Z"].toInt());
        scene->addItem(item);
        listElem << item;

        if (item->id()==7) {
            item->setWidth(obj["W"].toInt());
            connect(item, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
        }

        if (item->id()==4) {
            item->setWidth(obj["W"].toInt());
            item->setHeight(obj["H"].toInt());
            connect(item, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
        }

        if (item->id()==8) {
           item->setByteArrCont(obj["CONTENT"].toVariant().toByteArray());
        }

        if (item->IsNodesElement()) {
            auto arrNodes = obj["NODES"].toArray();
            for(const auto& ArrNode: arrNodes) {
                GrawItem *itemNode = ComponentFactory::createComponent(ComponentType::GraphNode);
                //itemNode->setParent(item);
                itemNode->setParentItem(item);

                auto obPosx = ArrNode.toArray();
                //itemNode->setParentItem(item);

                //itemNode->setPtX(obPosx[0].toInt());
                //itemNode->setPtY(obPosx[1].toInt());
                itemNode->setX(obPosx[0].toInt());
                itemNode->setY(obPosx[1].toInt());


                connect(itemNode, &GrawItem::signalParent, item, &GrawItem::isUpdateChild);
                //item->AddPoint(itemNode);
                // listElem << itemNode;
                //scene->addItem(itemNode);
            }
            item->update();
            connect(item, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
        }

        auto arrProperty = obj["PROPERTY"].toArray();
        if (arrProperty.count()>0) {
            for (const auto& ArrNodeP: arrProperty) {
                auto ObjProp = ArrNodeP.toObject();
                for (const QString& keyProp: ObjProp.keys()) {
                    item->setProperty(keyProp, ObjProp[keyProp].toVariant());
                    if (item->id()==5 and keyProp=="COLOR")
                        item->setProperty(keyProp, ObjProp[keyProp].toVariant().value<QColor>());
                }
            }
        }
    }
    fillTable();
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

void MainWindow::fillFilesShems() const
{
    QStringList List;

    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(QStringList("*.aqjs"));
    dir.setSorting(QDir::Size);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        //qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        //QTreeWidgetItem *treeItem = new QTreeWidgetItem;
        //treeItem->setText(columnIndex, fileInfo.fileName());
        //treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::SvgItem));
        //category4TreeItem->addChild(treeItem);
        List << fileInfo.fileName();
    }

    model->setStringList(List);
    ui->lvFiles->setModel(model);
    ui->lvFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::fillComponentLibrary() const
{
    const int columnIndex = 0;

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setAlternatingRowColors(true);

    QTreeWidgetItem *treeItem1 = new QTreeWidgetItem(ui->treeWidget);
    treeItem1->setText(columnIndex, "Елемент лінії");
    treeItem1->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Line));

    QTreeWidgetItem *treeItem2 = new QTreeWidgetItem(ui->treeWidget);
    treeItem2->setText(columnIndex, "Муфта-кабель");
    treeItem2->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Arrow));

    QTreeWidgetItem *treeItem3 = new QTreeWidgetItem(ui->treeWidget);
    treeItem3->setText(columnIndex, "Текст");
    treeItem3->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::RectangleText));

    QTreeWidgetItem *treeItem4 = new QTreeWidgetItem(ui->treeWidget);;
    treeItem4->setText(columnIndex, "Лінія-полілінія");
    treeItem4->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::Polyline));


    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(columnIndex, "Подвійний текст");
    treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::TwoText));

    //QTreeWidgetItem *treeItem2 = new QTreeWidgetItem (ui->treeWidget);
    //treeItem2->setText(columnIndex, "svg item");
    //treeItem2->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::SvgItem));

    QTreeWidgetItem *category4TreeItem = new QTreeWidgetItem(ui->treeWidget);
    category4TreeItem->setText(columnIndex, "Інші елементи");
    {
        QDir dir;
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setNameFilters(QStringList("assel_*.svg"));
        //dir.setNameFilters(QStringList("*.svg"));
        dir.setSorting(QDir::Size);

        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            //qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
            QTreeWidgetItem *treeItem = new QTreeWidgetItem;
            treeItem->setText(columnIndex, fileInfo.fileName());
            treeItem->setData(columnIndex, componentTypeRole, qVariantFromValue(ComponentType::SvgItem));
            category4TreeItem->addChild(treeItem);
        }
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

void MainWindow::fillTblProp(const GrawItem *item) const
{
    QList<QPair<QString, QString>> listProp = item->getListPropText();
    if (listProp.count()>0) {
        if (!ui->tWProperty->isVisible())
            ui->tWProperty->setVisible(true);

        ui->tWProperty->setRowCount(0);
        QStringList heaVert;
        for (int i=0; i<listProp.count(); i++) {
            ui->tWProperty->insertRow(i);
            heaVert.append(listProp.at(i).second);
            QVariant varProp = item->getPropVariant(listProp.at(i).first);
            if (varProp.isNull())
                ui->tWProperty->setItem(i,0,new QTableWidgetItem("[null]"));
            else{
                if (varProp.typeName()==tr("QString")) {
                    ui->tWProperty->setItem(i,0,new QTableWidgetItem(varProp.toString()));
                }else{
                    if (varProp.typeName()==tr("int") or varProp.typeName()==tr("double")) {
                        ui->tWProperty->setItem(i,0,new QTableWidgetItem(QString::number(varProp.toInt())));
                    }else{
                        if (varProp.typeName()==tr("QColor")) {
                            ui->tWProperty->setItem(i,0,new QTableWidgetItem(varProp.toString()));
                            ui->tWProperty->item(i,0)->setBackground(varProp.value<QColor>());
                        }else{
                            if (varProp.typeName()==tr("bool")) {
                                if (varProp.toBool())
                                    ui->tWProperty->setItem(i,0,new QTableWidgetItem("Так"));
                                else
                                    ui->tWProperty->setItem(i,0,new QTableWidgetItem("Ні"));
                            }else
                                ui->tWProperty->setItem(i,0,new QTableWidgetItem("["+QString(varProp.typeName())+"]"));
                        }
                    }
                }
            }
        }
        ui->tWProperty->setVerticalHeaderLabels(heaVert);
        ui->tWProperty->resizeColumnsToContents();
        ui->tWProperty->horizontalHeader()->setStretchLastSection(true);
    }else {
        ui->tWProperty->setVisible(false);
    }
}

void MainWindow::CloneElement(const GrawItem *item)
{
    GrawItem *newgraw = ComponentFactory::createComponent(item->id());
    newgraw->setX(item->x()+10);
    newgraw->setY(item->y()+10);
    newgraw->setRotation(item->rotation());
    newgraw->setZValue(item->zValue());

    if (newgraw->id()==7) {
        newgraw->setWidth(item->boundingRect().width());
        connect(newgraw, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
    }

    if (newgraw->id()==4) {
        newgraw->setWidth(item->boundingRect().width());
        newgraw->setHeight(item->boundingRect().height());
        connect(newgraw, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
    }

    if (newgraw->IsNodesElement()) {
        for (const GrawItem *ni : item->GetPoints()) {
            GrawItem *itemNode = ComponentFactory::createComponent(ComponentType::GraphNode);
            itemNode->setParentItem(newgraw);
            itemNode->setX(ni->x());
            itemNode->setY(ni->y());
            connect(itemNode, &GrawItem::signalParent, newgraw, &GrawItem::isUpdateChild);
        }
        newgraw->update();
        connect(newgraw, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
    }

    if (newgraw->componentType()==ComponentType::SvgItem) {
        newgraw->setByteArrCont(item->getByteArrCont());
    }

    QList<QPair<QString, QString>> listProp = item->getListPropText();
    if (listProp.count()>0) {
        for (int k=0; k<listProp.count(); k++) {
            QVariant varProp = item->getPropVariant(listProp.at(k).first);
            if (varProp.isNull())
                continue;
            newgraw->setProperty(listProp[k].first, varProp);
        }
    }

    scene->addItem(newgraw);
    listElem << newgraw;
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
    if (graw->IsNodesElement()) {
        GrawItem *grawV = ComponentFactory::createComponent(ComponentType::GraphNode);
        grawV->setTypeParent(var.toInt());
        draftItem = grawV;
    }
    else{
        //draftItem = graw;
        if (graw->id()==8) {
            QString filename = QDir::currentPath() + "/"+item->text(column);
            if(QFileInfo::exists(filename)) {
                qDebug() << filename;
                QFile file(filename);
                if(file.open(QIODevice::ReadOnly)) {
                    QByteArray ba = file.readAll();
                    graw->setByteArrCont(ba);
                }
            }
            //item->text()
        }
        draftItem = graw;
    }

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
        for (int i=0; i<listElem.size(); i++)
        {
            const GrawItem *grawsel = listElem[i];
            if (grawsel->isSelected()) {
                ui->tableWidget->selectRow(i);

                fillTblProp(grawsel);

                return;
            }
        }
        return;
    }

    if (!draftItem)
        return;

    GrawItem *newItem;
    if (draftItem->getTypeParent()>0)
        newItem = ComponentFactory::createComponent(draftItem->getTypeParent());
    else
        newItem = ComponentFactory::createComponent(draftItem->componentType());

    if (newItem->id()==8) {
        newItem->setByteArrCont(draftItem->getByteArrCont());
    }

    if (!newItem->IsNodesElement() or !PolyItem) {
        newItem->setPos(draftItem->pos());
        scene->addItem(newItem);
        listElem.append(newItem);

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, new QTableWidgetItem((QString::number(newItem->x()))));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1, new QTableWidgetItem((QString::number(newItem->y()))));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(""));
        ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1,16);
    }

    if (newItem->id()==4 or newItem->id()==7) {
        connect(newItem, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
    }

    if (newItem->IsNodesElement()) {
        newItem->AddPoint();
        connect(newItem, &GrawItem::updScen, scene, &MyGraphicsScene::UpdateScen);
        if (!PolyItem) {
            PolyItem=newItem;
        }else{
            PolyItem->AddPoint(draftItem->pos());

            for (int k=0; k<PolyItem->GetPoints().count(); k++) {
                GrawItem *grawvyzol = PolyItem->GetPoints()[k];

                bool addscene=true;
                for (int i=0; i<listElem.count(); i++)
                {
                    const GrawItem *grawitem = listElem[i];
                    if  (grawvyzol == grawitem) {
                        addscene=false;
                        break;
                    }
                }
                if (addscene) {
                    connect(grawvyzol, &GrawItem::signalParent, PolyItem, &GrawItem::isUpdateChild);
                    grawvyzol->setDeltaX(0);
                    grawvyzol->setDeltaY(0);
                    grawvyzol->setParentItem(PolyItem);
                    listElem.append(grawvyzol);
                    //scene->addItem(grawvyzol);
                }
            }
            PolyItem->update();
        }
    }else{
        setSceneState(SceneState::NormalState); //Коли додано новий елемент то занулюємо статус
    }
    //newItem->AddPoint(QPointF(2,5));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << QKeySequence(event->key()).toString();

    if (event->key()==Qt::Key_D) {
        //InsertNode()
        for (GrawItem *itmBMode : listElem)
        {
            if (itmBMode->isSelected()) {
                CloneElement(itmBMode);
            }
        }
        return;
    }

    if (event->key()==Qt::Key_I) {
        for (GrawItem *insitemnode : listElem)
        {
            if (insitemnode->id()==5) {
                insitemnode->InsertNode();
            }
        }
        return;
    }

    if (event->key()==Qt::Key_B) {
        //InsertNode()
        for (GrawItem *itmBMode : listElem)
        {
            if (itmBMode->isSelected()) {
                qDebug() << itmBMode->zValue();
                if (itmBMode->zValue()>0) {
                    itmBMode->setZValue(0);
                }else{
                    itmBMode->setZValue(1);
                }
            }
        }
        return;
    }

    if (state==SceneState::NormalState) {
        if (event->key()==Qt::Key_Control) {
            for (int i=0; i<listElem.size(); ++i)
            {
                GrawItem *grawitem = listElem[i];

                grawitem->setSelected(false);

                if (! grawitem->IsNodesElement()) {
                    continue;
                }

                grawitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                grawitem->setFlag(QGraphicsItem::ItemIsMovable, true);
            }
            return;
        }
    }

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

            for (GrawItem *delitem : listElem)
            {
                if (delitem->id()==5) {
                    delitem->DeleteSelectNode();
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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Control) {
        for (int i=0; i<listElem.size(); ++i)
        {
            GrawItem *grawitem = listElem[i];
            if (!grawitem->IsNodesElement())
                continue;

            if (grawitem->isSelected())
                continue;

            grawitem->setFlag(QGraphicsItem::ItemIsSelectable, false);
            grawitem->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
        return;
    }
}

void MainWindow::on_actionSvg_triggered()
{
    //qDebug() << " Scene has " << scene->items().count() << " items" ;
    int maxX = 0;
    int maxY = 0;

    for (QGraphicsItem *ItemScene : scene->items())
    {
        if ((ItemScene->x()+ItemScene->boundingRect().width())>maxX)
            maxX = ItemScene->x()+ItemScene->boundingRect().width();

        if (ItemScene->y()+ItemScene->boundingRect().height()>maxY)
            maxY = ItemScene->y()+ItemScene->boundingRect().height();

    }
    maxX = maxX + 10;
    maxY = maxY + 10;


    QRectF rs = scene->sceneRect();
    scene->setSceneRect(0,0,maxX,maxY);
    //scene->setSceneState(SceneState::SaveSvgFile);

    QSvgGenerator svgGen;

    svgGen.setFileName( "scene2svg.svg" );
    svgGen.setSize(QSize(scene->width(), scene->height()));
    svgGen.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    svgGen.setTitle(tr("SVG Generator Example Drawing"));
    svgGen.setDescription(tr("An SVG drawing created by the SVG Generator "
                             "Example provided with Qt."));

    QPainter painter( &svgGen );
    scene->render( &painter );

    scene->setSceneRect(0,0,rs.width(), rs.height());
    //scene->setSceneState(SceneState::NormalState);
    //qDebug() << " Svg Save" ;
}

void MainWindow::on_tWProperty_cellDoubleClicked(int row, int column)
{
    qDebug() << "on_tWProperty_cellDoubleClicked" << row << column;
    if (column==0) {
        if (state != SceneState::CreateComponentState)
        {
            for (int i=0; i<listElem.size(); ++i)
            {
                GrawItem *grawsel = listElem[i];
                if (grawsel->isSelected()) {

                    QList<QPair<QString, QString>> listProp = grawsel->getListPropText();
                    QVariant varProp = grawsel->getPropVariant(listProp.at(row).first);

                    QString txtProp = grawsel->getListPropText().at(row).first;
                    QString txtPropT = grawsel->getListPropText().at(row).second;

                    qDebug() << varProp.isNull() << grawsel->id() << varProp.typeName();
                    if ( (varProp.isNull() and grawsel->id()==7) or (varProp.typeName()==tr("QString") and !varProp.isNull())
                        or (varProp.isNull() and grawsel->id()==4 and txtProp=="TEXT") )
                    {

                        //qDebug() << txtProp;
                        bool ok;
                        QString text = QInputDialog::getText(this, "Параметр: " + txtPropT,
                                                             txtPropT+":", QLineEdit::Normal,
                                                             varProp.toString(), &ok);
                        if (ok && !text.isEmpty()) {
                            //textLabel->setText(text);
                            grawsel->setProperty(txtProp,text);
                            fillTblProp(grawsel);
                        }
                    }
                    if ((varProp.isNull() and grawsel->id()==5 and txtProp=="COLOR")
                        or (varProp.typeName()==tr("QColor") and !varProp.isNull())) {

                        QColor color = QColorDialog::getColor(varProp.value<QColor>(), this);
                        if( color.isValid() )
                        {
                            grawsel->setProperty(txtProp,color);
                            fillTblProp(grawsel);
                        }
                    }
                    if ((varProp.isNull() and grawsel->id()==5 and txtProp=="WIDTH2")
                        or (varProp.typeName()==tr("int") and !varProp.isNull())
                        or ((grawsel->id()==4 or grawsel->id()==5) and varProp.typeName()==tr("double") and !varProp.isNull())
                        or (varProp.isNull() and grawsel->id()==4 and txtProp=="SIZE")
                        ) {

                        bool ok;
                        int ipar = QInputDialog::getInt(this,  "Параметр: " + txtPropT,
                                                     txtPropT+":", varProp.toInt(), 1, 32, 1, &ok);
                        if (ok) {
                            grawsel->setProperty(txtProp,ipar);
                            fillTblProp(grawsel);
                        }
                    }
                    if ( (varProp.isNull() and grawsel->id()==4 and txtProp=="BOLD")
                        or (varProp.typeName()==tr("bool")) ) {
                        if (varProp.isNull()) {
                            grawsel->setProperty(txtProp,false);
                        }else{
                            grawsel->setProperty(txtProp,!varProp.toBool());
                        }
                        fillTblProp(grawsel);
                    }

                    break;
                }
            }
        }
    }
}

void MainWindow::on_actSSPrint_triggered()
{


}

void MainWindow::on_actSSReadOnly_triggered()
{
    int maxX = 0;
    int maxY = 0;

    for (QGraphicsItem *ItemScene : scene->items())
    {
        if ((ItemScene->x()+ItemScene->boundingRect().width())>maxX)
            maxX = ItemScene->x()+ItemScene->boundingRect().width();

        if (ItemScene->y()+ItemScene->boundingRect().height()>maxY)
            maxY = ItemScene->y()+ItemScene->boundingRect().height();

        GrawItem *ItemViewMode = dynamic_cast<GrawItem*>(ItemScene);
        if (ItemViewMode)
            ItemViewMode->setModeView(1);


    }
    maxX = maxX + 10;
    maxY = maxY + 10;

    scene->setSceneRect(0,0,maxX,maxY);
    scene->setSceneState(SceneState::ReadOnlyState);

    state = SceneState::ReadOnlyState;
}

void MainWindow::on_actSSNormal_triggered()
{
    for (QGraphicsItem *ItemScene : scene->items())
    {
        GrawItem *ItemViewMode = dynamic_cast<GrawItem*>(ItemScene);
        if (ItemViewMode)
            ItemViewMode->setModeView(0);
    }

    scene->setSceneRect(0,0,20000,20000);
    scene->setSceneState(SceneState::NormalState);

    state = SceneState::NormalState;
}

void MainWindow::on_lvFiles_doubleClicked(const QModelIndex &index)
{
    QModelIndex ind = ui->lvFiles->currentIndex();
    QString itemText = ind.data(Qt::DisplayRole).toString();
    _FileNameJSC = itemText;
    this->setWindowTitle(_WindowsTitle+"["+_FileNameJSC+"]");
    loadGraphFile();
    fillFilesShems();

    //qDebug() << "on_lvFiles_doubleClicked" <<itemText;
}

void MainWindow::on_action_triggered()
{
    scene->clear();
    listElem.clear();

    QString str = QUuid::createUuid().toString();
    _FileNameJSC = str + ".aqjs";
    this->setWindowTitle(_WindowsTitle+"["+_FileNameJSC+"]");
    fillFilesShems();
}

void MainWindow::on_action_2_triggered()
{
    saveGraphFile();
    fillFilesShems();
}

void MainWindow::on_actInsMakros_triggered()
{
    //bool ok;
    //QString text = QInputDialog::getMultiLineText(this, tr("QInputDialog::getMultiLineText()"),
    //                                              tr("Address:"), "John Doe\nFreedom Street", &ok);
    //if (ok && !text.isEmpty())
    //    multiLineTextLabel->setText(text);
    QStringList items;
    QStringList itemsFile;

    QDir dir;
    dir.setPath("makros");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(QStringList("*.mkjs"));
    dir.setSorting(QDir::Size);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        itemsFile << "makros//"+fileInfo.fileName();
        qDebug()<<fileInfo.fileName();

        QFile filejs("makros//"+fileInfo.fileName());
        filejs.open(QIODevice::ReadOnly);

        QByteArray saveData = filejs.readAll();
        QJsonDocument DocJs(QJsonDocument::fromJson(saveData));
        auto array = DocJs.array();
        QString tMakros="";
        for(const auto& json: array)
        {
            auto obj = json.toObject();

            if (obj["ID"].toInt()==-2) {
                tMakros = obj["NAME"].toString();

                break;
            }
        }
        if (tMakros=="")
            items<<fileInfo.fileName();
        else
            items<<tMakros;
    }

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Оберіть макрос"),
        tr("Макрос:"), items, 0, false, &ok);

    if (ok && !item.isEmpty()) {
        int indx = items.indexOf(item);
        _FileNameJSC = itemsFile[indx];
        loadGraphFile();
        _FileNameJSC = "";
        this->setWindowTitle(_WindowsTitle);
    }
}

void MainWindow::on_actNewMakros_triggered()
{
    saveGraphFile(true);
}

void MainWindow::on_action_4_triggered()
{
    qreal minX = scene->width();
    qreal minY = scene->height();
    //qDebug()<<minX<<minY;
    for (QGraphicsItem *ItemScene : scene->items())
    {
        if (ItemScene->x()<minX)
            minX = ItemScene->x();

        if (ItemScene->y()<minY)
            minY = ItemScene->y();
    }

    minX = minX - 20;
    minY = minY - 20;
    // qDebug()<<minX<<minY;

    if (minX>0 or minY>0) {
        for (QGraphicsItem *ItemScene : scene->items())
        {
            ItemScene->setX(ItemScene->x()-minX);
            ItemScene->setY(ItemScene->y()-minY);
        }
        scene->update();
    }

}

void MainWindow::on_action_5_triggered()
{
    for (QGraphicsItem *ItemScene : scene->items())
    {
        GrawItem *item = static_cast<GrawItem *>(ItemScene);
        if (item->id()==5)
            item->setZValue(2);
    }
}

void MainWindow::on_action_6_triggered()
{
    for (QGraphicsItem *ItemScene : scene->items())
    {
        GrawItem *item = static_cast<GrawItem *>(ItemScene);
        if (item->id()==5)
            item->setZValue(0);
    }
}
