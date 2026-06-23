#include "ConfigReader.h"

#include "Core/Minimal.h"

#include <fstream>

Source::Core::ApplicationConfig ConfigReader::Read(int Argc, char **Argv)
{
    Source::Core::ApplicationConfig Config = ParseCliArguments(Argc, Argv);
    ReadSettingsJson(Config);
    return Config;
}

Source::Core::ApplicationConfig ConfigReader::ParseCliArguments(int Argc, char **Argv)
{
    Source::Core::ApplicationConfig Config;

    for (int I = 0; I < Argc; I++)
    {
        std::string Arg = Argv[I];

        if (Arg == "-game")
        {
            Config.LaunchType = Source::Core::LaunchType::Game;
        }

        if (Arg == "-editor")
        {
            Config.LaunchType = Source::Core::LaunchType::Editor;
        }

        if (Arg == "-hide")
        {
            Config.WindowConfig.RenderWindow = false;
        }

        if (Arg == "-host" && I + 1 < Argc)
        {
            Config.EditorConfig.Host = Argv[++I];
        }

        if (Arg == "-port" && I + 1 < Argc)
        {
            Config.EditorConfig.EditorPort = std::stoi(Argv[++I]);
        }

        if (Arg == "-width" && I + 1 < Argc)
        {
            Config.WindowConfig.Width = std::stoi(Argv[++I]);
        }

        if (Arg == "-height" && I + 1 < Argc)
        {
            Config.WindowConfig.Height = std::stoi(Argv[++I]);
        }

        if (Arg == "-vsync" && I + 1 < Argc)
        {
            Config.WindowConfig.UseVSync = std::stoi(Argv[++I]) != 0;
        }
    }

    return Config;
}

void ConfigReader::ReadSettingsJson(Source::Core::ApplicationConfig& Config)
{
    std::ifstream File("Settings.json");

    if (!File)
    {
        return;
    }

    Json SettingsJson;
    File >> SettingsJson;

    if (SettingsJson.contains("height"))
    {
        Config.WindowConfig.Height = SettingsJson["height"].get<uint32>();
    }


    if (SettingsJson.contains("width"))
    {
        Config.WindowConfig.Width = SettingsJson["width"].get<uint32>();
    }
}
