#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class WorkspaceModule final : public Core::IModule
    {
    public:
        Core::TickPolicy GetTickPolicy() const override { return Core::TickPolicy::Always; }
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;

    private:
        void RotateCamera(const Core::Context& Context);
        void MoveCamera(const Core::Context& Context);
    };
}