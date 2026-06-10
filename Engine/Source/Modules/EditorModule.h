#pragma once

#include "../Core/IModule.h"

namespace Source::Modules
{
    class EditorModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;
    };
}