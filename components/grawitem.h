#pragma once

#include "componenttype.h"
#include <QGraphicsItem>

/*!
 * \brief The GrawItem is the base abstract class for all components.
 */
class GrawItem : public QGraphicsItem
{
public:
    explicit GrawItem(int id);

    virtual ComponentType componentType() const = 0;
    int id() const;
    void RotateFlip();
    bool IsVyzlElement();
    virtual void AddPoint(const QPointF &pos);
    int _type_parent{0};
    virtual QVector<GrawItem*> GetPoints() const;
    virtual void setDeltaX(qreal iDeltaX);
    virtual void setDeltaY(qreal iDeltaY);

    virtual void setPtX(qreal iptX);
    virtual void setPtY(qreal iptY);

    virtual QPointF getPoint() const;

    void setParentItem(QGraphicsItem *parent);

public slots:
   virtual void isUpdateChild();

signals:
   void signalParent();

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int _id{-1};
};
