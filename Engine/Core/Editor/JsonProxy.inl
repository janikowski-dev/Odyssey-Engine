#pragma once

#include "JsonProxy.h"

namespace Engine::Editor
{
    template<typename... Ts>
    void JsonProxy::RegisterInbound(EventList<Ts...>)
    {
        (RegisterInbound<Ts>(EventKey<Ts>::Value), ...);
    }

    template<typename... Ts>
    void JsonProxy::RegisterOutbound(EventList<Ts...>)
    {
        (RegisterOutbound<Ts>(EventKey<Ts>::Value), ...);
    }
    
    template<typename T>
    void JsonProxy::RegisterInbound(const std::string& Name)
    {
        Inbound[Name] = [this](const Json& Data)
        {
            Bus.Enqueue<T>(Data.get<T>());
        };
    }

    template<typename T>
    void JsonProxy::RegisterOutbound(const std::string& Name)
    {
        Subscriptions.push_back(
            Bus.Subscribe<T>([this, Name](T& Event)
            {
                if (Sink)
                {
                    Sink(Name, Json(Event));
                }
            })
        );
    }
}
