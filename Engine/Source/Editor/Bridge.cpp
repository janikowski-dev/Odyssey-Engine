#include "Editor/Bridge.h"
#include "Bridge.h"

namespace Source::Editor
{
    bool Bridge::Start(std::string Host, uint16 Port) { return Connection.Listen(Host, Port); }

    void Bridge::Communicate()
    {
        for (const std::string& Raw : Connection.Poll())
        {
            HandleMessage(Raw);
        }
    }

    void Bridge::HandleMessage(const std::string &Raw)
    {
        Json Message = Json::parse(Raw, nullptr, false);

        if (IsValid(Message))
        {
            HandleRpc(Message);
        }
    }

    void Bridge::HandleRpc(const Json& Message)
    {
        const std::string Method = Message["method"].get<std::string>();
        const Json Data = Message.value("data", Json::object());
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
                Response["error"] = "Unknown method: " + Method;
            }
        }
        else
        {
            try
            {
                Json Result = It->second(Data);
                
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

    bool Bridge::IsValid(const Json &Message)
    {
        if (Message.is_discarded())
        {
            return false;
        }

        return Message.contains("method") && Message["method"].is_string();
    }
}
