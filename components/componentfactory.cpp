#include "componentfactory.h"
#include "arrowitem.h"
#include "lineitem.h"
#include "grawitem.h"

GrawItem *ComponentFactory::createComponent(ComponentType type)
{
    switch (type)
    {
    case ComponentType::Arrow:
        return new ArrowItem(static_cast<int>(ComponentType::Arrow));

    case ComponentType::Line:
        return new LineItem(static_cast<int>(ComponentType::Line));
    }

    return nullptr;
}

GrawItem *ComponentFactory::createComponent(int id)
{
    return createComponent(static_cast<ComponentType>(id));
}
