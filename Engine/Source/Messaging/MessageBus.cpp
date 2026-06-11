#include "MessageBus.h"

namespace Source::Messaging
{
    void MessageBus::Flush()
    {
        std::deque<QueuedMessage> Local;
        {
            std::lock_guard Lock(Mutex);
            std::swap(Local, Queue);
        }

        for (auto& Event : Local)
        {
            std::vector<HandlerEntry> Snapshot;
            {
                std::lock_guard Lock(Mutex);
                auto It = Handlers.find(Event.TypeId);

                if (It == Handlers.end())
                {
                    continue;
                }

                It->second.Sort();
                Snapshot = It->second.Entries;
            }

            for (auto& Entry : Snapshot)
            {
                Entry.Callback(Event.Data.get());
            }
        }
    }

    void MessageBus::Unsubscribe(SubId Id)
    {
        std::lock_guard Lock(Mutex);

        for (auto& [Type, List] : Handlers)
        {
            List.Remove(Id);
        }
    }
}
