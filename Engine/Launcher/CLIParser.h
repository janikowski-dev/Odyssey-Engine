#pragma once

#include "Config/ApplicationConfig.h"

class CLIParser
{
public:
    static Core::Config::ApplicationConfig Parse(int argc, char** argv);
};