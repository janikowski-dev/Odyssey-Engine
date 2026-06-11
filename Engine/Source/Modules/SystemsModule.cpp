#include "SystemsModule.h"

#include "../Messaging/MessageBus.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Mesh.h"
#include "../ECS/Registry.h"
#include "../Components/RendererComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/SpinComponent.h"

namespace Source::Modules
{
    SystemsModule::SystemsModule() = default;
    SystemsModule::~SystemsModule() = default;

    void SystemsModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitRendering();
        InitTime();
        InitSystems(Config, Context);
    }

    void SystemsModule::Tick(const Core::Context& Context)
    {
        HandleTime();
        UpdateSystems(Context);
    }

    void SystemsModule::InitRendering()
    {
        RendererBackend = MakeUnique<Rendering::Renderer>();
    }

    void SystemsModule::InitTime()
    {
        LastTime = Clock::now();
    }

    void SystemsModule::InitSystems(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();
        Context.World->Add<Components::CameraComponent>(Context.World->Create(), Components::CameraComponent{ { 4.0f, 3.0f, 6.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } });
    }

    void SystemsModule::HandleTime()
    {
        CurrentTime = Clock::now();
        DeltaTime = Duration(CurrentTime - LastTime).count();
        LastTime = CurrentTime;
    }

    void SystemsModule::UpdateSystems(const Core::Context& Context)
    {
        Context.World->View<Components::TransformComponent, Components::SpinComponent>(
            [this](ECS::Entity, Components::TransformComponent& T, Components::SpinComponent& S)
            {
                T.Rotation += S.Speed * DeltaTime;
            }
        );

        Components::CameraComponent* ActiveCamera = nullptr;

        Context.World->View<Components::CameraComponent>(
            [&ActiveCamera](ECS::Entity, Components::CameraComponent& C)
            {
                if (!ActiveCamera || C.Priority > ActiveCamera->Priority)
                {
                    ActiveCamera = &C;
                }
            }
        );

        if (!ActiveCamera)
        {
            return;
        }

        RendererBackend->Begin(*ActiveCamera);

        Context.World->View<Components::TransformComponent, Components::RendererComponent>(
            [this, ActiveCamera](ECS::Entity, Components::TransformComponent& T, Components::RendererComponent& R)
            {
                RendererBackend->DrawMesh(T.Matrix(), *R.Mesh, *R.Shader, R.Color);
            }
        );

        RendererBackend->End();
    }
}