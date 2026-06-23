#pragma once

#include "Core/ApplicationConfig.h"

class ConfigReader
{
public:
    static Source::Core::ApplicationConfig Read(int Argc, char** Argv);

private:
    static void ParseCliArguments(Source::Core::ApplicationConfig& Config, int Argc, char **Argv);
    static void ReadSettingsJson(Source::Core::ApplicationConfig& Config);
};