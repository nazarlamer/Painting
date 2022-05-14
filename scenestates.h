#pragma once

#include <QMetaType>

enum class SceneState
{
    CreateComponentState,
    NormalState,
    ReadOnlyState,
    PrintState
};

// for QVariant support
Q_DECLARE_METATYPE(SceneState)
