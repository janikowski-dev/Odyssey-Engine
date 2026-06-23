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

    struct EditorConfig
    {
        std::string Host;
        int EditorPort;
    };

    struct ApplicationConfig
    {
        EngineConfig EngineConfig;
        WindowConfig WindowConfig;
        EditorConfig EditorConfig;
        LaunchType LaunchType;
    };
}