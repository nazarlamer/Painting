#pragma once

#include <QList>
#include <QPair>

namespace PropertyItem
{

struct Item
{
    QPair<QString, QString> prText;
    QPair<QString, int> prValueInt;
    QPair<QString, QString> prValueStr;
};

}

class GrItProperty : public QList<PropertyItem::Item>
{

public:
    explicit GrItProperty();

    //int id() const;

    QList<QPair<QString, QString>> getListPropText() const;

    void addProperty(const QString ifirst, const QString iopus, const int iValue);
    void addProperty(const QString ifirst, const QString iopus, const QString iValue);

};
