#pragma once

#include "Editor/Connection.h"
#include "Core/Minimal.h"

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <type_traits>

namespace Source::Editor
{
    class Bridge
    {
    public:
        using Handler = std::function<Json(const Json& Params)>;

        bool Start(std::string Host, uint16 Port);
        void Communicate();

        template<typename TIn, typename TOut, typename TFunction>
        void On(std::string_view Method, TFunction&& Function);
        
        template<typename TIn>
        void Send(std::string_view Method, TIn Data);

    private:
        void HandleMessage(const std::string& Raw);
        void HandleRpc(const Json& Message);
        bool IsValid(const Json& Message);

        std::unordered_map<std::string, Handler> Handlers;
        Connection Connection;
    };
}

#include "Bridge.inl"