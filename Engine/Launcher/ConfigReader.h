#pragma once

#include "Core/ApplicationConfig.h"

class ConfigReader
{
public:
    static Source::Core::ApplicationConfig Read(int Argc, char** Argv);

private:
    static Source::Core::ApplicationConfig ParseCliArguments(int Argc, char** Argv);
    static void ReadSettingsJson(Source::Core::ApplicationConfig& Config);
};