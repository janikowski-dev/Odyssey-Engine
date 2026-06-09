#pragma once

#include "WindowConfig.h"
#include "LaunchType.h"

namespace Core::Config
{
    struct ApplicationConfig
    {
        WindowConfig WindowConfig;
        LaunchType LaunchType;
        int EditorPort;
    };
}