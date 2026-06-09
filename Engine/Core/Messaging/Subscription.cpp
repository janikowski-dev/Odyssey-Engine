#include "Subscription.h"

#include "EventBus.h"

namespace Engine::Messaging
{
    Subscription::Subscription(Subscription&& Other) noexcept
    {
        Copy(Other);
        Invalidate(Other);
    }

    Subscription::~Subscription()
    {
        Reset();
    }

    Subscription& Subscription::operator=(Subscription&& Other) noexcept
    {
        if (this == &Other)
        {
            return *this;
        }

        Reset();
        Copy(Other);
        Invalidate(Other);
        return *this;
    }

    void Subscription::Reset()
    {
        if (!Bus)
        {
            return;
        }

        if (Id == INVALID_SUB)
        {
            return;
        }

        Bus->Unsubscribe(Id);
        Bus = nullptr;
        Id = INVALID_SUB;
    }

    void Subscription::Copy(Subscription& Other)
    {
        Bus = Other.Bus;
        Id  = Other.Id;
    }

    void Subscription::Invalidate(Subscription& Other)
    {
        Other.Bus = nullptr;
        Other.Id = INVALID_SUB;
    }
}
