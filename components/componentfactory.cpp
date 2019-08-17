#include "componentfactory.h"
#include "arrowitem.h"
#include "lineitem.h"
#include "grawitem.h"
#include "circleitem.h"
#include "rectangleitem.h"

GrawItem *ComponentFactory::createComponent(ComponentType type)
{
    switch (type)
    {
    case ComponentType::Arrow:
        return new ArrowItem(static_cast<int>(type));

    case ComponentType::Line:
        return new LineItem(static_cast<int>(type));

    case ComponentType::Circle:
        return new CircleItem(static_cast<int>(type));

    case ComponentType::Rectangle:
        return new RectangleItem(static_cast<int>(type));

    default:
        return nullptr;
    }
}

GrawItem *ComponentFactory::createComponent(int id)
{
    return createComponent(static_cast<ComponentType>(id));
}
