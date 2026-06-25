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

    enum class LaunchType
    {
        Editor,
        Game
    };

	struct EngineConfig
	{
        std::string SettingsName = "Launch.odysettings";
        std::string SceneName = "Level.odyscene";
        std::string Resources = "Resources";
        std::string Root = "";

        std::string GetSettingsPath() const
        {
            return (std::filesystem::path(Root) / SettingsName).string();
        }
        
        std::string GetScenePath() const
        {
            return (std::filesystem::path(Root) / SceneName).string();
        }
        
        std::string GetResourcesPath() const
        {
            return (std::filesystem::path(Root) / Resources).string();
        }
	};

    struct EditorConfig
    {
        std::string Host = "";
        int EditorPort = 0;
    };

    struct ApplicationConfig
    {
        EngineConfig EngineConfig;
        WindowConfig WindowConfig;
        EditorConfig EditorConfig;
        LaunchType LaunchType = LaunchType::Game;
    };
}