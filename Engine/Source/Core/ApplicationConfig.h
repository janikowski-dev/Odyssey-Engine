#pragma once

#include "Core/Minimal.h"

namespace Source::Core
{
	struct WindowConfig
	{
		uint32 Width = 1280;
		uint32 Height = 720;
		bool IsResizeable = true;
		bool UseVSync = true;
		bool RenderWindow = true;
	};

    enum LaunchType
    {
        Editor,
        Game
    };

	struct EngineConfig
	{
        std::string ProjectFilePath;
	};

    struct ApplicationConfig
    {
        EngineConfig EngineConfig;
        WindowConfig WindowConfig;
        LaunchType LaunchType;
        std::string Host;
        int EditorPort;
    };
}