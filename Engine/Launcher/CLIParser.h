#pragma once

#include "ApplicationConfig.h"

class CLIParser
{
public:
    static Core::ApplicationConfig Parse(int argc, char** argv);
};