#include "Modules/SerializationModule.h"

#include "Events/GetSchema.h"
#include "Events/ModifyEntity.h"
#include "Serialization/ReflectionHandler.h"
#include "Serialization.generated.h"

namespace Source::Modules
{
    void SerializationModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Attach(*Context.EditorBridge, *Context.World);
        Serialization::Init(*Context.World);
    }

    void SerializationModule::Attach(Editor::Bridge& Bridge, ECS::Registry& World)
    {
        Bridge.On<Events::ModifyEntityRequest, Events::ModifyEntityResponse>(Events::ModifyEntityKey, [&World](const Events::ModifyEntityRequest& Request)
        {
            Serialization::SetComponent(World.Get(Request.Index), Request.Component, Request.Fields);
            DebugLog << Request.Fields.dump();
            return Events::ModifyEntityResponse();
        });

        Bridge.On<Events::GetSchemaRequest, Events::GetSchemaResponse>(Events::GetSchemaKey, [](const Events::GetSchemaRequest&)
        {
            return Events::GetSchemaResponse { Serialization::GetComponentTypes() };
        });
    }
}

