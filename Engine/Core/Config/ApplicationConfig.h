#pragma once

#include "WindowConfig.h"
#include "EngineConfig.h"
#include "LaunchType.h"

namespace Core::Config
{
    struct ApplicationConfig
    {
        EngineConfig EngineConfig;
        WindowConfig WindowConfig;
        LaunchType LaunchType;
        int EditorPort;
    };
}