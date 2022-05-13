#include "twogtext.h"
#include <QPainter>
#include <QDebug>

Twogtext::Twogtext(int id) : GrawItem(id)
{

}

QRectF Twogtext::boundingRect() const
{

}

void Twogtext::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

ComponentType Twogtext::componentType() const
{
    return ComponentType::TwoText;
}
