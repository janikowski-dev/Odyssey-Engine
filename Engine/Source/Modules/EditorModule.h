#pragma once

#include "Messaging/Subscription.h"
#include "Core/IModule.h"

namespace Source::Modules
{
    class EditorModule final : public Core::IModule
    {
    public:
        Core::TickPolicy GetTickPolicy() const override { return Core::TickPolicy::Always; }
        
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;

        void Tick(const Core::Context& Context) override;

    private:
        void InitBridge(const Core::ApplicationConfig Config, Core::Context& Context);
        void InitIncomingEvents(const Core::ApplicationConfig Config, Core::Context& Context);
        void InitOutgoingEvents(const Core::ApplicationConfig Config, Core::Context& Context);

    private:
        Messaging::Subscription DestroyedEntitySubscribtion;
        Messaging::Subscription CreatedEntitySubscribtion;
    };
}