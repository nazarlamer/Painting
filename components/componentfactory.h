/*Фабрика*/
#pragma once

#include "componenttype.h"

class GrawItem;

class ComponentFactory
{
public:
    ComponentFactory() = delete;

    static GrawItem *createComponent(ComponentType type);
    static GrawItem *createComponent(int id);
};

