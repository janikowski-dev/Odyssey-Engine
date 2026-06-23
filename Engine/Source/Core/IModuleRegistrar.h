#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Core
{
    class IModuleRegistrar
    {
    public:
        virtual void RegisterModule(UniquePtr<IModule> Module) = 0;
    };
}