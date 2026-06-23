#include "Core/Application.h"
#include "CLIParser.h"

int main(int Argc, char** Argv)
{
    Source::Core::ApplicationConfig Config = CLIParser::Parse(Argc, Argv);
    Source::Core::Application Application(Config);
    Application.Run();
    return 0;
}