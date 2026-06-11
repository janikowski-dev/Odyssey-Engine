#pragma once

#include "HandlerData.h"

#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Source::Messaging
{
    class Subscription;

    class MessageBus
    {
    public:
        template<typename T>
        [[nodiscard]] Subscription Subscribe(std::function<void(T&)> Handler, int Priority = 0);

        void Unsubscribe(SubId Id);

        template<typename T>
        void Publish(T& InEvent);

        template<typename T>
        void Enqueue(T InEvent);

        void Flush();

    private:
        struct QueuedMessage
        {
            SharedPtr<void> Data;
            std::type_index TypeId;
        };

        mutable std::mutex Mutex;
        std::unordered_map<std::type_index, HandlerList> Handlers;
        std::deque<QueuedMessage> Queue;
        SubId NextId = 1;
    };
}

#include "MessageBus.inl"
