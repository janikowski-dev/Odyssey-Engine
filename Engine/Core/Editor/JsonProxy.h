#pragma once

#include "../Messaging/EventBus.h"
#include "../Messaging/Subscription.h"

#include <nlohmann/json.hpp>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Core::Editor
{
    template<typename... Ts>
    struct EventList
    {
    };
 
    template<typename T>
    struct EventKey
    {
    };

    class JsonProxy
    {
    public:
        using Json = nlohmann::json;
        using OutSink = std::function<void(const std::string& Name, const Json& Data)>;

        explicit JsonProxy(Messaging::EventBus& InBus) : Bus(InBus) {}
 
        template<typename... Ts>
        void RegisterInbound(EventList<Ts...>);

        template<typename... Ts>
        void RegisterOutbound(EventList<Ts...>);

        void SetSink(OutSink InSink) { Sink = std::move(InSink); }

        bool Dispatch(const std::string& Name, const Json& Data);

    private:
        template<typename T>
        void RegisterInbound(const std::string& Name);

        template<typename T>
        void RegisterOutbound(const std::string& Name);

    private:
        using Parser = std::function<void(const Json&)>;

        std::vector<Messaging::Subscription> Subscriptions;
        std::unordered_map<std::string, Parser> Inbound;
        Messaging::EventBus& Bus;
        OutSink Sink;
    };
}

#define ENGINE_EVENT_KEY(Type, Key)                  \
    template<> struct Core::Editor::EventKey<Type> \
    {                                                \
        static constexpr const char* Value = Key;    \
    }

#include "JsonProxy.inl"
