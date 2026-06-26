#include "Modules/RenderingModule.h"

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Passes/GridPass.h"
#include "Rendering/Passes/MeshPass.h"
#include "Rendering/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"
#include "Rendering/Camera.h"
#include "Components/CameraComponent.h"
#include "ECS/Registry.h"

namespace Source::Modules
{
    RenderingModule::RenderingModule() = default;
    RenderingModule::~RenderingModule() = default;

    void RenderingModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Passes.push_back(MakeUnique<Rendering::GridPass>(Context));
        Passes.push_back(MakeUnique<Rendering::MeshPass>(Context));
        Backend = MakeUnique<Rendering::Backend>();
    }

    void RenderingModule::Tick(const Core::Context& Context)
    {
        Components::CameraComponent* Camera = nullptr;

        Context.World->View<Components::CameraComponent>(
            [&Camera](ECS::Entity, Components::CameraComponent& C)
            {
                if (!Camera || C.Priority > Camera->Priority)
                {
                    Camera = &C;
                }
            }
        );

        if (!Camera)
        {
            return;
        }

        Rendering::Camera ActiveCamera(
            Camera->Position,
            Camera->Rotation,
            Camera->FovDegrees,
            Camera->Aspect,
            Camera->Near,
            Camera->Far
        );

        Backend->Begin(ActiveCamera);

        for (const auto& Pass : Passes)
        {
            Pass->Execute(*Backend);
        }

        Backend->End();
    }
}