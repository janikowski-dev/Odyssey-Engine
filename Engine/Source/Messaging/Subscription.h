#pragma once

#include "HandlerData.h"

#include "../Core/Types.h"

namespace Source::Messaging
{
    class MessageBus;

    class Subscription
    {
    public:
        Subscription() = default;
        Subscription(MessageBus* Bus, SubID Id) : Bus(Bus), Id(Id) {}
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
        MessageBus* Bus = nullptr;
        SubID Id = INVALID_SUB;
    };
}
