#pragma once

#include <QList>
#include <QPair>

namespace PropertyItem
{

struct Item
{
    QPair<QString, QString> prText;
    QPair<QString, QVariant> prValue;
};

}

class GrItProperty : public QList<PropertyItem::Item>
{

public:
    explicit GrItProperty();

    QList<QPair<QString, QString>> getListPropText() const;

    void addProperty(const QString ifirst, const QString iopus);

    void setProperty(const QString ifirst, const QVariant iValue);

    QVariant getPropVariant(QString ifirst) const;

private:


};
