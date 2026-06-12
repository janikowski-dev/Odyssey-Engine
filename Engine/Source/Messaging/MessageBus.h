#pragma once

#include "Messaging/HandlerData.h"

#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

namespace Source::Messaging
{
    class Subscription;

    class MessageBus
    {
    public:
        template<typename TMessage>
        [[nodiscard]] Subscription Subscribe(std::function<void(TMessage&)> Handler, int Priority = 0);

        void Unsubscribe(SubId Id);

        template<typename TMessage>
        void Publish(TMessage& InMessage);

        template<typename TMessage>
        void Enqueue(TMessage InMessage);

        void Flush();

    private:
        struct QueuedMessage
        {
            std::type_index TypeId;
            SharedPtr<void> Data;
        };

        std::unordered_map<std::type_index, HandlerList> Handlers;
        std::deque<QueuedMessage> Queue;
        mutable std::mutex Mutex;
        SubId NextId = 1;
    };
}

#include "MessageBus.inl"
