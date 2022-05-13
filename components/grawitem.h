#pragma once

#include "componenttype.h"
#include <QGraphicsItem>

/*!
 * \brief The GrawItem is the base abstract class for all components.
 */
class GrawItem : public QGraphicsObject
{  Q_OBJECT
public:
    explicit GrawItem(int id);

    virtual ComponentType componentType() const = 0;
    int id() const;
    void RotateFlip();
    bool IsNodesElement() const;
    /*
    Абстрактний класс GrawItem, від якого наслідуються зараз усі фігури, говорить, що у нього можна додавати точки.
    Коло є GrawItem, бо наслідується від нього. Чи є сенс додавати точки в коло? ООП, Карл!!!

    Як то правильно би правильно мало б бути. Деяким GrawItem це потрібно.
    */
    virtual void AddPoint(const QPointF &pos);
    virtual void AddPoint(GrawItem *igi);

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
   void updScen();

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int _id{-1};
};
