#pragma once

#include <cstdint>
#include <functional>
#include <vector>

namespace Core::Messaging
{
    using SubID = std::uint64_t;
    inline constexpr SubID INVALID_SUB = 0;

    struct HandlerEntry
    {
        std::function<void(void*)> Callback;
        int Priority = 0;
        SubID Id = INVALID_SUB;
    };

    struct HandlerList
    {
        void Remove(SubID Id);
        void Sort();

        std::vector<HandlerEntry> Entries;
        bool IsDirty = false;
    };
}
