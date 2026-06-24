#include "Modules/EditorModule.h"

#include "Events/GetViewport.h"
#include "Events/SelectEntity.h"
#include "Events/SaveScene.h"
#include "Events/LoadScene.h"
#include "Events/Ping.h"
#include "Events/ModifyEntity.h"
#include "Events/Play.h"
#include "Events/Stop.h"
#include "Events/GetSchema.h"
#include "Events/GetEntities.h"
#include "Events/CreatedEntity.h"
#include "Events/DestroyedEntity.h"
#include "Serialization/SceneSerializer.h"
#include "Serialization/ReflectionHandler.h"

namespace Source::Modules
{
    void EditorModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitBridge(Config, Context);
        InitIncomingEvents(Config, Context);
        InitOutgoingEvents(Config, Context);
    }

    void EditorModule::Tick(const Core::Context& Context)
    {
        Context.EditorBridge->Communicate();
    }

    void EditorModule::InitBridge(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.EditorBridge = MakeUnique<Editor::Bridge>();
        Context.EditorBridge->Start(Config.EditorConfig.Host, Config.EditorConfig.EditorPort);
    }

    void EditorModule::InitIncomingEvents(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.EditorBridge->On<Events::ModifyEntityRequest, Events::ModifyEntityResponse>(Events::ModifyEntityKey, [&Context](const Events::ModifyEntityRequest& Request)
        {
            Serialization::SetComponent(Context.World->Get(Request.Index), Request.Component, Request.Fields);
            return Events::ModifyEntityResponse();
        });

        Context.EditorBridge->On<Events::SelectEntityRequest, Events::SelectEntityResponse>(Events::SelectEntityKey, [&Context](const Events::SelectEntityRequest& Request)
        {
            return Events::SelectEntityResponse { Serialization::GetComponents(Context.World->Get(Request.Index)) };
        });

        Context.EditorBridge->On<Events::GetSchemaRequest, Events::GetSchemaResponse>(Events::GetSchemaKey, [](const Events::GetSchemaRequest&)
        {
            return Events::GetSchemaResponse { Serialization::GetComponentTypes() };
        });

        Context.EditorBridge->On<Events::PingRequest, Events::PingResponse>(Events::PingKey, [](const Events::PingRequest&)
        {
            return Events::PingResponse();
        });

        Context.EditorBridge->On<Events::SaveSceneRequest, Events::SaveSceneResponse>(Events::SaveSceneKey, [&Context](const Events::SaveSceneRequest& Request)
        {
            Serialization::SaveScene(*Context.World);
            return Events::SaveSceneResponse();
        });

        Context.EditorBridge->On<Events::LoadSceneRequest, Events::LoadSceneResponse>(Events::LoadSceneKey, [&Context](const Events::LoadSceneRequest& Request)
        {
            Serialization::LoadScene(*Context.World);
            return Events::LoadSceneResponse();
        });

		Context.EditorBridge->On<Events::GetViewportRequest, Events::GetViewportResponse>(Events::GetViewportKey, [&Context](const Events::GetViewportRequest&)
    	{
    	    return Events::GetViewportResponse { Context.Window->GetHandle() };
    	});

		Context.EditorBridge->On<Events::PlayRequest, Events::PlayResponse>(Events::PlayKey, [&Context](const Events::PlayRequest&)
    	{
            Context.Runtime->ShouldBePlaying = true;
    	    return Events::PlayResponse();
    	});

		Context.EditorBridge->On<Events::StopRequest, Events::StopResponse>(Events::StopKey, [&Context](const Events::StopRequest&)
    	{
            Context.Runtime->ShouldBePlaying = false;
    	    return Events::StopResponse();
    	});

        Context.EditorBridge->On<Events::GetEntitiesRequest, Events::GetEntitiesResponse>(Events::GetEntitiesKey, [&Context](const Events::GetEntitiesRequest&)
        {
            std::vector<uint32> Indexes;

            Context.World->Each([&](ECS::Entity Entity)
            {
                Indexes.push_back(Entity.Index);
            });

            return Events::GetEntitiesResponse { std::move(Indexes) };
        });
    }

    void EditorModule::InitOutgoingEvents(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World->OnEntityDestroyed += [&Context](uint32 Index)
        {
            Context.EditorBridge->Send(Events::DestroyedEntityKey, Events::DestroyedEntity { Index });
        };

        Context.World->OnEntityCreated += [&Context](uint32 Index)
        {
            Context.EditorBridge->Send(Events::CreatedEntityKey, Events::CreatedEntity { Index });
        };
    }
}
