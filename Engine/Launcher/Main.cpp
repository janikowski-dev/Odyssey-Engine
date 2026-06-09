#include "Application.h"
#include "CLIParser.h"

int main(int argc, char** argv)
{
    Core::Config::ApplicationConfig Config = CLIParser::Parse(argc, argv);
    Core::Application Application(Config);
    Application.Run();
    return 0;
}