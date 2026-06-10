#pragma once

#include "../IModule.h"

namespace Core::Modules
{
    class EditorModule final : public IModule
    {
    public:
        void Init(const ApplicationConfig Config, Context& Context) override;
        void Tick(const Context& Context) override;
    };
}