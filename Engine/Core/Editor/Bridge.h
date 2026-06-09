#pragma once

#include "Connection.h"

#include "Messaging/EventBus.h"
#include "JsonProxy.h"

#include <nlohmann/json.hpp>

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

namespace Core::Editor
{
    class Bridge
    {
    public:
        using Json = nlohmann::json;
        using Handler = std::function<Json(const Json& Params)>;

        explicit Bridge(Messaging::EventBus& InBus);

        bool Start(std::uint16_t Port);
        void Tick();
        bool IsConnected() const;

        void On(const std::string& Method, Handler InHandler);

        void SendEvent(const std::string& Name, const Json& Data);

        template<typename... Ts>
        void RegisterInbound(EventList<Ts...> List)  { Proxy.RegisterInbound(List); }

        template<typename... Ts>
        void RegisterOutbound(EventList<Ts...> List) { Proxy.RegisterOutbound(List); }

    private:
        void HandleMessage(const std::string& Raw);
        void HandleRpc(const Json& Message);

        std::unordered_map<std::string, Handler> Handlers;
        Connection Connection;
        JsonProxy Proxy;
    };
}
