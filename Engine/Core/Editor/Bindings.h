#pragma once

#include "JsonProxy.h"

#include "../Events/Placeholder.h"

namespace Engine::Events
{
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Placeholder, Handle);
}

ENGINE_EVENT_KEY(Engine::Events::Placeholder, "placeholder");

namespace Engine::Editor
{
    using EditorOutbound = EventList<Events::Placeholder>;
    using EditorInbound = EventList<Events::Placeholder>;
}