#include "Bridge.h"

namespace Source::Editor
{
    bool Bridge::Start(uint16 Port)
    {
        return Connection.Listen(Port);
    }

    void Bridge::SendEvent(const std::string& Name, const Json& Data)
    {
        Json Message;
        Message["event"] = Name;
        Message["data"] = Data;
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

        if (Message.contains("method") && Message["method"].is_string())
        {
            HandleRpc(Message);
        }
    }

    void Bridge::HandleRpc(const Json& Message)
    {
        const std::string Method = Message["method"].get<std::string>();
        const Json Params = Message.value("params", Json::object());
        const bool HasId = Message.contains("id");

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
