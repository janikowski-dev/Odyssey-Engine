#include "EventBus.h"

namespace Engine::Messaging
{
    void EventBus::Flush()
    {
        std::deque<QueuedEvent> Local;
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

    void EventBus::Unsubscribe(SubID Id)
    {
        std::lock_guard Lock(Mutex);

        for (auto& [Type, List] : Handlers)
        {
            List.Remove(Id);
        }
    }
}
