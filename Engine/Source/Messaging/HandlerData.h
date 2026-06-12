#pragma once

#include "Core/Minimal.h"

namespace Source::Messaging
{
    using SubId = uint64;
    inline constexpr SubId INVALID_SUB = 0;

    struct HandlerEntry
    {
        std::function<void(void*)> Callback;
        int Priority = 0;
        SubId Id = INVALID_SUB;
    };

    struct HandlerList
    {
        void Remove(SubId Id);
        void Sort();

        std::vector<HandlerEntry> Entries;
        bool IsDirty = false;
    };
}
