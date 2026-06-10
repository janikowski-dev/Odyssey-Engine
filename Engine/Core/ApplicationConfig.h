#pragma once

#include "Config/WindowConfig.h"
#include "Config/EngineConfig.h"
#include "Config/LaunchType.h"

namespace Core
{
    struct ApplicationConfig
    {
        Config::EngineConfig EngineConfig;
        Config::WindowConfig WindowConfig;
        Config::LaunchType LaunchType;
        int EditorPort;
    };
}