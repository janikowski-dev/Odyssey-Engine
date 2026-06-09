#include "CLIParser.h"

Core::Config::ApplicationConfig CLIParser::Parse(int argc, char **argv)
{
    Core::Config::ApplicationConfig config;

    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "-game")
        {
            config.LaunchType = Core::Config::LaunchType::Game;
        }

        if (arg == "-editor")
        {
            config.LaunchType = Core::Config::LaunchType::Editor;
        }

        if (arg == "-hide")
        {
            config.WindowConfig.RenderWindow = false;
        }

        if (arg == "-port" && i + 1 < argc)
        {
            config.EditorPort = std::stoi(argv[++i]);
        }

        if (arg == "-width" && i + 1 < argc)
        {
            config.WindowConfig.Width = std::stoi(argv[++i]);
        }

        if (arg == "-height" && i + 1 < argc)
        {
            config.WindowConfig.Height = std::stoi(argv[++i]);
        }

        if (arg == "-vsync" && i + 1 < argc)
        {
            config.WindowConfig.UseVSync = std::stoi(argv[++i]) != 0;
        }
    }

    return config;
}
