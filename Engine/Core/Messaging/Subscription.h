#pragma once

#include "HandlerData.h"

namespace Engine::Messaging
{
    class EventBus;

    class Subscription
    {
    public:
        Subscription() = default;
        Subscription(EventBus* Bus, SubID Id) : Bus(Bus), Id(Id) {}
        Subscription(Subscription&& Other) noexcept;
        Subscription(const Subscription&) = delete;

        Subscription& operator=(const Subscription&) = delete;
        Subscription& operator=(Subscription&& Other) noexcept;

        ~Subscription();

        void Reset();
        bool IsValid() const { return Bus != nullptr && Id != INVALID_SUB; }
        SubID GetId() const { return Id; }

    private:
        void Copy(Subscription& Other);
        void Invalidate(Subscription& Other);

    private:
        EventBus* Bus = nullptr;
        SubID Id = INVALID_SUB;
    };
}
