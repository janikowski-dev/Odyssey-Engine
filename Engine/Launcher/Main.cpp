#include "Application.h"
#include "CLIParser.h"

int main(int argc, char** argv)
{
    Engine::Config::ApplicationConfig Config = CLIParser::Parse(argc, argv);
    Engine::Application Application(Config);
    Application.Run();
    return 0;
}