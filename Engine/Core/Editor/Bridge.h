#pragma once

#include "Connection.h"

#include "../Types.h"

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <type_traits>

namespace Core::Editor
{
    class Bridge
    {
    public:
        using Handler = std::function<Json(const Json& Params)>;

        bool Start(uint16 Port);
        void Tick();

        template<typename TIn, typename TOut, typename Fn>
        void On(std::string_view Method, Fn&& Function);

        void SendEvent(const std::string& Name, const Json& Data);

    private:
        void HandleMessage(const std::string& Raw);
        void HandleRpc(const Json& Message);

        std::unordered_map<std::string, Handler> Handlers;
        Connection Connection;
    };
}

#include "Bridge.inl"