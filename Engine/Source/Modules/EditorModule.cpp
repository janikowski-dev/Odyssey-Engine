#include "Modules/EditorModule.h"

#include "Events/GetViewport.h"
#include "Events/SelectEntity.h"
#include "Events/SaveScene.h"
#include "Events/LoadScene.h"
#include "Events/Ping.h"
#include "Events/ModifyEntity.h"
#include "Events/GetSchema.h"
#include "Events/AddedEntity.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Messages/AddedEntityMessage.h"
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
		Context.EditorBridge->On<Events::GetViewportRequest, Events::GetViewportResponse>(Events::GetViewportKey, [&Context](const Events::GetViewportRequest&)
    	{
    	    return Events::GetViewportResponse { Context.Window->GetHandle() };
    	});
        
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
            return Events::SaveSceneResponse();
        });

        Context.EditorBridge->On<Events::LoadSceneRequest, Events::LoadSceneResponse>(Events::LoadSceneKey, [&Context](const Events::LoadSceneRequest& Request)
        {
            Context.World->View<Components::RendererComponent>(
                [&Context](ECS::Entity, Components::RendererComponent& R)
                {
                    R.Shader = Context.ResourceCache->Shaders.Get(R.ShaderId);
                    R.Mesh = Context.ResourceCache->Meshes.Get(R.MeshId);
                }
            );

            return Events::LoadSceneResponse();
        });
    }

    void EditorModule::InitOutgoingEvents(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        AddedEntitySubscribtion = Context.MessageBus->Subscribe<Messages::AddedEntityMessage>([&Context](const Messages::AddedEntityMessage& M)
        {
            Context.EditorBridge->Send(Events::AddedEntityKey, Events::AddedEntity { M.Index });
        });
    }
}
