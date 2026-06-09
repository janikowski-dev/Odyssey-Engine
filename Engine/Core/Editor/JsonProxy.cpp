#include "JsonProxy.h"

namespace Core::Editor
{
    bool JsonProxy::Dispatch(const std::string& Name, const Json& Data)
    {
        auto It = Inbound.find(Name);

        if (It == Inbound.end())
        {
            return false;
        }

        try
        {
            It->second(Data);
        }
        catch (const Json::exception&)
        {
            return false;
        }

        return true;
    }
}
