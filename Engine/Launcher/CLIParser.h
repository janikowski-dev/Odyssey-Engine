#pragma once

#include "Core/ApplicationConfig.h"

class CLIParser
{
public:
    static Source::Core::ApplicationConfig Parse(int argc, char** argv);
};