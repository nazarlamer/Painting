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

void GrItProperty::addProperty(const QString ifirst, const QString iopus, const int iValue)
{
    PropertyItem::Item iItProp;
    iItProp.prText.first = ifirst;
    iItProp.prText.second = iopus;

    iItProp.prValueInt.first = ifirst;
    iItProp.prValueInt.second = iValue;
    append(iItProp);

}

void GrItProperty::addProperty(const QString ifirst, const QString iopus, const QString iValue)
{
    PropertyItem::Item iItProp;
    iItProp.prText.first = ifirst;
    iItProp.prText.second = iopus;

    iItProp.prValueStr.first = ifirst;
    iItProp.prValueStr.second = iValue;
    append(iItProp);
}

