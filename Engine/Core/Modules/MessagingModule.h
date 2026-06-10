#pragma once

#include "../IModule.h"
#include "../Messaging/MessageBus.h"

namespace Core::Modules
{
    class MessagingModule final : public IModule
    {
    public:
        void Init(const ApplicationConfig Config, Context& Context) override;
        void Tick(const Context& Context) override;
    };
}