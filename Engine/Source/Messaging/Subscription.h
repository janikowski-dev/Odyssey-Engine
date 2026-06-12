#pragma once

#include "HandlerData.h"

#include "Core/Minimal.h"

namespace Source::Messaging
{
    class MessageBus;

    class Subscription
    {
    public:
        Subscription() = default;
        Subscription(MessageBus* Bus, SubId Id) : Bus(Bus), Id(Id) {}
        Subscription(Subscription&& Other) noexcept;
        Subscription(const Subscription&) = delete;

        Subscription& operator=(const Subscription&) = delete;
        Subscription& operator=(Subscription&& Other) noexcept;

        ~Subscription();

        void Reset();
        bool IsValid() const { return Bus != nullptr && Id != INVALID_SUB; }
        SubId GetId() const { return Id; }

    private:
        void Copy(Subscription& Other);
        void Invalidate(Subscription& Other);

    private:
        MessageBus* Bus = nullptr;
        SubId Id = INVALID_SUB;
    };
}
