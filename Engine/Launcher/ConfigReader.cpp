#include "ConfigReader.h"

#include "Core/Minimal.h"

Source::Core::ApplicationConfig ConfigReader::Read(int Argc, char **Argv)
{
    Source::Core::ApplicationConfig Config = Source::Core::ApplicationConfig();
    ParseCliArguments(Config, Argc, Argv);
    ReadSettingsJson(Config);
    return Config;
}

void ConfigReader::ParseCliArguments(Source::Core::ApplicationConfig& Config, int Argc, char **Argv)
{
    for (int I = 0; I < Argc; I++)
    {
        std::string Arg = Argv[I];

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

        if (Arg == "-root" && I + 1 < Argc)
        {
            Config.EngineConfig.Root = Argv[++I];
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
}

void ConfigReader::ReadSettingsJson(Source::Core::ApplicationConfig& Config)
{
    if (Config.LaunchType == Source::Core::LaunchType::Editor)
    {
        return;
    }

    std::ifstream File(Config.EngineConfig.GetScenePath());

    if (!File)
    {
        return;
    }

    Json SettingsJson;
    File >> SettingsJson;

    if (SettingsJson.contains("Height"))
    {
        Config.WindowConfig.Height = SettingsJson["Height"].get<uint32>();
    }

    if (SettingsJson.contains("Width"))
    {
        Config.WindowConfig.Width = SettingsJson["Width"].get<uint32>();
    }

    if (SettingsJson.contains("VSync"))
    {
        Config.WindowConfig.UseVSync = SettingsJson["VSync"].get<uint32>() != 0;
    }
}
