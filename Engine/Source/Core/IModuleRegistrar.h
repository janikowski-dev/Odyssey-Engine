#pragma once

#include "Core/IModule.h"

namespace Source::Core
{
    class IModuleRegistrar
    {
    public:
        virtual void RegisterModule(IModule* module) = 0;
    };
}