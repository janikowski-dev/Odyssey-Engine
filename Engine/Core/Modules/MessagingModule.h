#pragma once

#include "../IModule.h"
#include "../Messaging/MessageBus.h"

namespace Core
{
    class MessagingModule final : public IModule
    {
    public:
        MessagingModule() = default;
        ~MessagingModule() override = default;

        void Init(const ApplicationConfig Config, Context& Context) override
        {
		    Context.MessageBus = MakeUnique<Messaging::MessageBus>();
        }

        void Tick(const Context& Context) override
        {
			Context.MessageBus->Flush();
        }
    };
}