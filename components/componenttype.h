#pragma once

#include <QMetaType>

enum class ComponentType
{
    None,
    Line,
    Arrow,
    Circle,
    Rectangle
};

// for QVariant support
Q_DECLARE_METATYPE(ComponentType)
