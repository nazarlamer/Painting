#include "giproperty.h"

GrItProperty::GrItProperty() : QList<PropertyItem::Item>()
{

}

QList<QPair<QString, QString>> GrItProperty::getListPropText() const
{
    QList<QPair<QString, QString>> ListText;
    for (int i=0; i<count(); i++ ) {
        ListText.append(QPair<QString, QString>(this->at(i).prText.first, this->at(i).prText.second));
    }
    return ListText;
}

void GrItProperty::addProperty(const QString ifirst, const QString iopus)
{
    PropertyItem::Item iItProp;
    iItProp.prText.first = ifirst;
    iItProp.prText.second = iopus;

    iItProp.prValue.first = ifirst;
    iItProp.prValue.second = QString(); //Null
    append(iItProp);
}

void GrItProperty::setProperty(const QString ifirst, const QVariant iValue)
{
    for (int i=0; i<count(); i++ ) {
        if (this->at(i).prValue.first == ifirst) {
            PropertyItem::Item editem;
            editem.prText = at(i).prText;
            editem.prValue.first = ifirst;
            editem.prValue.second = iValue;
            this->replace(i,editem);
            break;
        }
    }
}

QVariant GrItProperty::getPropVariant(QString ifirst) const
{
    QVariant outVariant{QString()};
    for (int i=0; i<count(); i++ ) {
        if (this->at(i).prValue.first == ifirst) {
            outVariant = this->at(i).prValue.second;
            break;
        }
    }

    return outVariant;
}

