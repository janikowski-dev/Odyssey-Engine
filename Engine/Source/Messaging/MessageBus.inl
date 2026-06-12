#pragma once

#include "Messaging/MessageBus.h"
#include "Messaging/Message.h"
#include "Messaging/Subscription.h"

namespace Source::Messaging
{
    template<typename TMessage>
    [[nodiscard]] Subscription MessageBus::Subscribe(std::function<void(TMessage&)> Handler, int Priority)
    {
        std::lock_guard Lock(Mutex);

        HandlerList& SpecificHandlers = Handlers[std::type_index(typeid(TMessage))];
        const SubId Id = NextId++;

        SpecificHandlers.Entries.push_back(HandlerEntry
        {
            [Handler = std::move(Handler)](void* Ptr)
            {
                Handler(*static_cast<TMessage*>(Ptr));
            },
            Priority,
            Id
        });
        
        SpecificHandlers.IsDirty = true;

        return Subscription(this, Id);
    }

    template<typename TMessage>
    void MessageBus::Publish(TMessage& InMessage)
    {
        const auto Key = std::type_index(typeid(TMessage));

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
            Entry.Callback(&InMessage);

            if constexpr (IsConsumable<TMessage>)
            {
                if (InMessage.Handled)
                {
                    break;
                }
            }
        }
    }

    template<typename TMessage>
    void MessageBus::Enqueue(TMessage InMessage)
    {
        std::lock_guard Lock(Mutex);

        Queue.push_back(QueuedMessage
        {
            MakeShared<TMessage>(std::move(InMessage)),
            std::type_index(typeid(TMessage))
        });
    }
}
