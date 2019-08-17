#pragma once

#include <QGraphicsItem>

class AbstractGraw : public QGraphicsItem
{
public:
    virtual int id() const = 0;
};
