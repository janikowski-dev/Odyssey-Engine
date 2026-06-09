#include "Bridge.h"

namespace Core::Editor
{
    Bridge::Bridge(Messaging::EventBus& InBus) : Proxy(InBus)
    {
        Proxy.SetSink([this](const std::string& Name, const Json& Data)
        {
            SendEvent(Name, Data);
        });
    }

    bool Bridge::Start(std::uint16_t Port)
    {
        return Connection.Listen(Port);
    }

    bool Bridge::IsConnected() const
    {
        return Connection.IsConnected();
    }

    void Bridge::On(const std::string& Method, Handler InHandler)
    {
        Handlers[Method] = std::move(InHandler);
    }

    void Bridge::SendEvent(const std::string& Name, const Json& Data)
    {
        Json Message;
        Message["event"] = Name;
        Message["data"]  = Data;
        Connection.Send(Message.dump());
    }

    void Bridge::Tick()
    {
        for (const std::string& Raw : Connection.Poll())
        {
            HandleMessage(Raw);
        }
    }

    void Bridge::HandleMessage(const std::string& Raw)
    {
        Json Message = Json::parse(Raw, nullptr, false);

        if (Message.is_discarded())
        {
            return;
        }

        if (Message.contains("event") && Message["event"].is_string())
        {
            const std::string Name = Message["event"].get<std::string>();
            const Json Data = Message.value("data", Json::object());
            Proxy.Dispatch(Name, Data);
            return;
        }

        if (Message.contains("method") && Message["method"].is_string())
        {
            HandleRpc(Message);
        }
    }

    void Bridge::HandleRpc(const Json& Message)
    {
        const std::string Method = Message["method"].get<std::string>();
        const Json Params = Message.value("params", Json::object());
        const bool HasId  = Message.contains("id");

        Json Response;

        if (HasId)
        {
            Response["id"] = Message["id"];
        }

        auto It = Handlers.find(Method);

        if (It == Handlers.end())
        {
            if (HasId)
            {
                Response["error"] = "unknown method: " + Method;
            }
        }
        else
        {
            try
            {
                Json Result = It->second(Params);
                
                if (HasId)
                {
                    Response["result"] = Result;
                }
            }
            catch (const std::exception& E)
            {
                if (HasId)
                {
                    Response["error"] = std::string(E.what());
                }
            }
        }

        if (HasId)
        {
            Connection.Send(Response.dump());
        }
    }
}
