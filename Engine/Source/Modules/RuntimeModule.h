#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Modules
{
    class RuntimeModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;
    
    private:
        Time LastTime {};
    };
}