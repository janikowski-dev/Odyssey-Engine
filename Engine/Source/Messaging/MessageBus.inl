#pragma once

#include "MessageBus.h"
#include "Message.h"
#include "Subscription.h"

#include "Core/Minimal.h"

#include <utility>

namespace Source::Messaging
{
    template<typename T>
    [[nodiscard]] Subscription MessageBus::Subscribe(std::function<void(T&)> Handler, int Priority)
    {
        std::lock_guard Lock(Mutex);

        HandlerList& SpecificHandlers = Handlers[std::type_index(typeid(T))];
        const SubId Id = NextId++;

        SpecificHandlers.Entries.push_back(HandlerEntry
        {
            [Handler = std::move(Handler)](void* Ptr)
            {
                Handler(*static_cast<T*>(Ptr));
            },
            Priority,
            Id
        });
        
        SpecificHandlers.IsDirty = true;

        return Subscription(this, Id);
    }

    template<typename T>
    void MessageBus::Publish(T& InEvent)
    {
        const auto Key = std::type_index(typeid(T));

        std::vector<HandlerEntry> Snapshot;
        {
            std::lock_guard Lock(Mutex);
            auto It = Handlers.find(Key);

            if (It == Handlers.end())
            {
                return;
            }

            It->second.Sort();
            Snapshot = It->second.Entries;
        }

        for (HandlerEntry& Entry : Snapshot)
        {
            Entry.Callback(&InEvent);

            if constexpr (IsConsumable<T>)
            {
                if (InEvent.Handled)
                {
                    break;
                }
            }
        }
    }

    template<typename T>
    void MessageBus::Enqueue(T InEvent)
    {
        std::lock_guard Lock(Mutex);

        Queue.push_back(QueuedMessage
        {
            MakeShared<T>(std::move(InEvent)),
            std::type_index(typeid(T))
        });
    }
}
