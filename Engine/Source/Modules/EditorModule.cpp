#include "Modules/EditorModule.h"

#include "Events/CreateCameraEntity.h"
#include "Events/SelectEntity.h"
#include "Events/CreateExampleEntity.h"
#include "Events/SaveScene.h"
#include "Events/LoadScene.h"
#include "Events/Ping.h"
#include "Events/ModifyEntity.h"
#include "Events/GetSchema.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Components/SpinComponent.h"
#include "Serialization/ReflectionHandler.h"

#include "Serialization.generated.h"

namespace Source::Modules
{
    void EditorModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Serialization::Init(*Context.World);
        InitBridge(Config, Context);
    }

    void EditorModule::Tick(const Core::Context& Context)
    {
        Context.EditorBridge->Communicate();
    }

    void EditorModule::InitBridge(const Core::ApplicationConfig Config, Core::Context &Context)
    {
        Context.EditorBridge = MakeUnique<Editor::Bridge>();
        
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

        Context.EditorBridge->On<Events::CreateExampleEntityRequest, Events::CreateExampleEntityResponse>(Events::CreateExampleEntityKey, [&Context](const Events::CreateExampleEntityRequest&)
        {
            ECS::Entity E = Context.World->Create();
            Context.World->Add<Components::TransformComponent>(E, Components::TransformComponent{ {-2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} });
            Context.World->Add<Components::RendererComponent>(E, Components::RendererComponent{ "lit", "cube", {0.85f, 0.30f, 0.22f}, Context.ResourceCache->Shaders.Get("lit"), Context.ResourceCache->Meshes.Get("cube") });
            Context.World->Add<Components::SpinComponent>(E, Components::SpinComponent{ {0.0f, 0.8f, 0.0f} });
            return Events::CreateExampleEntityResponse { E.Index };
        });

        Context.EditorBridge->On<Events::CreateCameraEntityRequest, Events::CreateCameraEntityResponse>(Events::CreateCameraEntityKey, [&Context](const Events::CreateCameraEntityRequest&)
        {
            ECS::Entity E = Context.World->Create();
            Context.World->Add<Components::CameraComponent>(E, Components::CameraComponent{ {4.0f, 3.0f, 6.0f} });
            return Events::CreateCameraEntityResponse { E.Index };
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

        Context.EditorBridge->Start(Config.EditorConfig.Host, Config.EditorConfig.EditorPort);
    }
}
