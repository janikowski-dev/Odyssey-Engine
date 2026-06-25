#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class TimeModule final : public Core::IModule
    {
    public:
        Core::TickPolicy GetTickPolicy() const override { return Core::TickPolicy::Playtime; }

        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        
        void OnBeginPlay(const Core::Context& Context) override;
        void OnEndPlay(const Core::Context& Context) override;

        void Tick(const Core::Context& Context) override;
    
    private:
        Time LastTime {};
    };
}