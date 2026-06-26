#include "Modules/RenderingModule.h"

#include "Components/CameraComponent.h"
#include "Rendering/Passes/GridPass.h"
#include "Rendering/Passes/MeshPass.h"
#include "Rendering/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"
#include "Rendering/Camera.h"
#include "ECS/Registry.h"

namespace Source::Modules
{
    RenderingModule::RenderingModule() = default;
    RenderingModule::~RenderingModule() = default;

    void RenderingModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        IsInEditor = Config.LaunchType == Core::LaunchType::Editor;

        if (IsInEditor)
        {
            EditorPasses.push_back(MakeUnique<Rendering::GridPass>(Context));
        }

        ProjectPasses.push_back(MakeUnique<Rendering::MeshPass>(Context));
        Backend = MakeUnique<Rendering::Backend>();
    }
    
    void RenderingModule::OnBeginPlay(const Core::Context &Context)
    {
        IsInPlay = true;
    }

    void RenderingModule::OnEndPlay(const Core::Context &Context)
    {
        IsInPlay = false;
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

        if (IsInEditor && !IsInPlay)
        {
            for (const auto& Pass : EditorPasses)
            {
                Pass->Execute(*Backend);
            }
        }

        for (const auto& Pass : ProjectPasses)
        {
            Pass->Execute(*Backend);
        }

        Backend->End();
    }
}