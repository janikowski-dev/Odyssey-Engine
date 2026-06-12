#include "Modules/SerializationModule.h"

#include "Events/GetSchema.h"
#include "Serialization/ReflectionHandler.h"
#include "Serialization.generated.h"

namespace Source::Modules
{
    void SerializationModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Serialization::BindECS(*Context.World);
        Attach(*Context.EditorBridge);
    }

    void SerializationModule::Attach(Editor::Bridge& Bridge)
    {
        Bridge.On<Events::GetSchemaRequest, Events::GetSchemaResponse>(Events::GetSchemaKey, [](const Events::GetSchemaRequest&)
        {
            return Events::GetSchemaResponse { Serialization::GetComponentTypes() };
        });
    }
}

