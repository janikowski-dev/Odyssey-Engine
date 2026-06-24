#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class SerializationModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void OnBeginPlay(const Core::Context& Context) override;
        void OnEndPlay(const Core::Context& Context) override;
    
    private:
        Json EditorScene;
    };
}