#include "Core/Application.h"
#include "CLIParser.h"

int main(int argc, char** argv)
{
    Source::Core::ApplicationConfig Config = CLIParser::Parse(argc, argv);
    Source::Core::Application Application(Config);
    Application.Run();
    return 0;
}