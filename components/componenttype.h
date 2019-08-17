#pragma once

#include <QMetaType>

enum class ComponentType
{
    Line,
    Arrow,
    Circle,
    Rectangle
};

// for QVariant support
Q_DECLARE_METATYPE(ComponentType)
