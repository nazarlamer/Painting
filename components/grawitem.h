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
    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int _id{-1};
};
