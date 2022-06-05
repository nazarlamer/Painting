#pragma once

#include <QMetaType>

enum class ComponentType
{
    None,
    Line,
    Arrow,
    Circle,
    RectangleText,
    Polyline,
    GraphNode,
    TwoText,
    SvgItem,
    Rectangle
};

// for QVariant support
Q_DECLARE_METATYPE(ComponentType)
