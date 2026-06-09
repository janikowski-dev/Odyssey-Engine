#pragma once

#include "Config/ApplicationConfig.h"

class CLIParser
{
public:
    static Engine::Config::ApplicationConfig Parse(int argc, char** argv);
};