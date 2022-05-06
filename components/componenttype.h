#pragma once

#include <QMetaType>

enum class ComponentType
{
    None,
    Line,
    Arrow,
    Circle,
    Rectangle,
    Polyline,
    PolylineMouse
};

// for QVariant support
Q_DECLARE_METATYPE(ComponentType)
