#pragma once

#include "Core/IModule.h"
#include "Messaging/MessageBus.h"

namespace Source::Modules
{
    class MessagingModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;
    };
}