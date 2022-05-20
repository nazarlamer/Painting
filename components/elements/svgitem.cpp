#include "svgitem.h"
#include <QDir>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QSvgRenderer>

/*
QFile file(QFileDialog::getOpenFileName(NULL, tr("Upload a file")));

// If the selected file is valid, continue with the upload
if (!file.fileName().isEmpty) {
    // Read the file and transform the output to a QByteArray
    QByteArray ba = file.readAll();

    // Send the QByteArray
    write(ba);
}
*/

SvgItem::SvgItem(int id) : GrawItem(id)
{
    QString filename = QDir::currentPath() + "/zap1_.svg";
    if(QFileInfo::exists(filename)) {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly)) {
            QByteArray ba = file.readAll();
            arrContent = ba;
            //arrContent.setRawData(ba, sizeof(ba));
            //arrContent.setRawData(ba, ba.size());
            //arrContent = QByteArray::fromRawData(ba, sizeof(ba));
            //QSvgRenderer *renderer = new QSvgRenderer(QLatin1String("zap1.svg"));
            QSvgRenderer *renderer = new QSvgRenderer(arrContent);
            QGraphicsSvgItem *svgit = new QGraphicsSvgItem();

            svgit->setSharedRenderer(renderer);
            svgit->setZValue(0);
            svgit->setFlag(QGraphicsItem::ItemIsMovable, false);
            svgit->setFlag(QGraphicsItem::ItemIsSelectable, false);
            svgitem = svgit;
        }
    }else{
        svgitem = nullptr;
    }
}

QRectF SvgItem::boundingRect() const
{
    if (svgitem) {
        return svgitem->boundingRect();
    }else {
        return QRectF(0,0,0,0);
    }
}

void SvgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (svgitem) {
        if (isSelected())
            paintSelected(painter);
        else
            paintNotSelected(painter);

        paintMain(painter, option, widget);
    }
}

ComponentType SvgItem::componentType() const
{
    return ComponentType::SvgItem;
}

QByteArray SvgItem::getByteArrCont()
{
    return arrContent;
}

void SvgItem::setByteArrCont(QByteArray iBAContent)
{
    arrContent = iBAContent;
    if (!svgitem) {
        QSvgRenderer *renderer = new QSvgRenderer(arrContent);
        QGraphicsSvgItem *svgit = new QGraphicsSvgItem();

        svgit->setSharedRenderer(renderer);
        svgit->setZValue(0);
        svgit->setFlag(QGraphicsItem::ItemIsMovable, false);
        svgit->setFlag(QGraphicsItem::ItemIsSelectable, false);
        svgitem = svgit;
        update();
    }
}

void SvgItem::paintSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(svgitem->boundingRect());
}

void SvgItem::paintNotSelected(QPainter *painter)
{
    painter->setPen(QPen(Qt::red, 1));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(svgitem->boundingRect());
}

void SvgItem::paintMain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    svgitem->paint(painter, option, widget);
}
