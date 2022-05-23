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
    SvgItem
};

// for QVariant support
Q_DECLARE_METATYPE(ComponentType)
