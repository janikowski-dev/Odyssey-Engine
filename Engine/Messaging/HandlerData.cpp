#include "HandlerData.h"

#include <algorithm>

namespace Engine::Messaging
{
    void HandlerList::Sort()
    {
        if (!IsDirty)
        {
            return;
        }

        std::stable_sort(Entries.begin(), Entries.end(),
            [](const HandlerEntry& A, const HandlerEntry& B)
            {
                return A.Priority > B.Priority;
            }
        );

        IsDirty = false;
    }

    void HandlerList::Remove(SubID Id)
    {
        Entries.erase(std::remove_if(Entries.begin(), Entries.end(), [Id](const HandlerEntry& Entry) { return Entry.Id == Id; }), Entries.end());
    }
}
