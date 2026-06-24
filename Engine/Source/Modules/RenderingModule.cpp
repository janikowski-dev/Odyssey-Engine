#include "Modules/RenderingModule.h"

#include "Messaging/MessageBus.h"
#include "Rendering/Renderer.h"
#include "Rendering/Mesh.h"
#include "ECS/Registry.h"
#include "Messages/CreatedEntityMessage.h"
#include "Components/RendererComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

namespace Source::Modules
{
    RenderingModule::RenderingModule() = default;
    RenderingModule::~RenderingModule() = default;

    void RenderingModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        RendererBackend = MakeUnique<Rendering::Renderer>();
    }

    void RenderingModule::Tick(const Core::Context& Context)
    {
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
                if (!R.Mesh)
                {
                    return;
                }

                if (!R.Shader)
                {
                    return;
                }
                
                RendererBackend->DrawMesh(T, *R.Mesh, *R.Shader, R.Color);
            }
        );

        RendererBackend->End();
    }
}