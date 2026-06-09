#pragma once

#include "JsonProxy.h"

#include "../Events/Placeholder.h"

namespace Core::Events
{
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Placeholder, Handle);
}

ENGINE_EVENT_KEY(Core::Events::Placeholder, "placeholder");

namespace Core::Editor
{
    using EditorOutbound = EventList<Events::Placeholder>;
    using EditorInbound = EventList<Events::Placeholder>;
}