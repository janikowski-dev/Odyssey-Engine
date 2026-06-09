#pragma once

#include "WindowConfig.h"
#include "LaunchType.h"

namespace Engine::Config
{
    struct ApplicationConfig
    {
        WindowConfig WindowConfig;
        LaunchType LaunchType;
        int EditorPort;
    };
}