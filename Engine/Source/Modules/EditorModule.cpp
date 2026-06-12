#include "EditorModule.h"

#include "Events/CreateEntity.h"
#include "Events/SaveScene.h"
#include "Events/LoadScene.h"
#include "Events/Ping.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Components/SpinComponent.h"

namespace Source::Modules
{
    void EditorModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.EditorBridge = MakeUnique<Editor::Bridge>();

        Context.EditorBridge->On<Events::PingRequest, Events::PingResponse>(Events::PingKey, [](const Events::PingRequest&)
        {
            return Events::PingResponse();
        });

        Context.EditorBridge->On<Events::CreateEntiryRequest, Events::CreateEntityResponse>(Events::CreateEntityKey, [&Context](const Events::CreateEntiryRequest&)
        {
            ECS::Entity E = Context.World->Create();
            Context.World->Add<Components::TransformComponent>(E, Components::TransformComponent{ {-2, 0, 0}, {0, 0, 0}, {1, 1, 1} });
            Context.World->Add<Components::RendererComponent>(E, Components::RendererComponent{ "lit", "cube", {0.85f, 0.30f, 0.22f}, Context.ResourceCache->Shaders.Get("lit"), Context.ResourceCache->Meshes.Get("cube") });
            Context.World->Add<Components::SpinComponent>(E, Components::SpinComponent{ {0.0f, 0.8f, 0.0f} });
            return Events::CreateEntityResponse();
        });

        Context.EditorBridge->On<Events::SaveSceneRequest, Events::SaveSceneResponse>(Events::SaveSceneKey, [&Context](const Events::SaveSceneRequest& Request)
        {
            Context.SceneSerializer->SaveToFile(*Context.World, Request.Path);
            Debug << "Saving";
            return Events::SaveSceneResponse();
        });

        Context.EditorBridge->On<Events::LoadSceneRequest, Events::LoadSceneResponse>(Events::LoadSceneKey, [&Context](const Events::LoadSceneRequest& Request)
        {
            Context.SceneSerializer->LoadFromFile(Request.Path, *Context.World);

            Context.World->View<Components::RendererComponent>(
                [&Context](ECS::Entity, Components::RendererComponent& R)
                {
                    R.Shader = Context.ResourceCache->Shaders.Get(R.ShaderId);
                    R.Mesh = Context.ResourceCache->Meshes.Get(R.MeshId);
                }
            );

            
            Context.World->Add<Components::CameraComponent>(Context.World->Create(), Components::CameraComponent{ { 4.0f, 3.0f, 6.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } });
            return Events::LoadSceneResponse();
        });

        Context.EditorBridge->Start(Config.Host, Config.EditorPort);
    }

    void EditorModule::Tick(const Core::Context& Context)
    {
        Context.EditorBridge->Communicate();
    }
}