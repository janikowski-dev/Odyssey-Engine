#include "Core/Application.h"
#include "ConfigReader.h"

int main(int Argc, char** Argv)
{
    Source::Core::ApplicationConfig Config = ConfigReader::Read(Argc, Argv);
    Source::Core::Application Application(Config);
    Application.Run();
    return 0;
}