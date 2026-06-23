#include "CLIParser.h"

Source::Core::ApplicationConfig CLIParser::Parse(int Argc, char **Argv)
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
            Config.Host = Argv[++I];
        }

        if (Arg == "-port" && I + 1 < Argc)
        {
            Config.EditorPort = std::stoi(Argv[++I]);
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
