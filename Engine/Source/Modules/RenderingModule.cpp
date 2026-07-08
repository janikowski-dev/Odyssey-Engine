#include "Modules/RenderingModule.h"

#include "Rendering/Passes/SelectionPass.h"
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

    void RenderingModule::Tick(const Core::Context& Context)
    {
        Render(GetActiveCamera(Context));
    }

    void RenderingModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        ProjectPasses.push_back(MakeUnique<Rendering::MeshPass>(Context));
        IsInEditor = Config.LaunchType == Core::LaunchType::Editor;
        Backend = MakeUnique<Rendering::Backend>();

        if (!IsInEditor)
        {
            return;
        }
        
        EditorPasses.push_back(MakeUnique<Rendering::SelectionPass>(Context));
        EditorPasses.push_back(MakeUnique<Rendering::GridPass>(Context));
    }
    
    void RenderingModule::OnBeginPlay(const Core::Context &Context)
    {
        IsInPlay = true;
    }

    void RenderingModule::OnEndPlay(const Core::Context &Context)
    {
        IsInPlay = false;
    }

    std::optional<Rendering::Camera> RenderingModule::GetActiveCamera(const Core::Context& Context)
    {
        if (IsInEditor && !IsInPlay)
        {
            return Rendering::Camera(
                Context.Workspace->CameraPosition,
                Context.Workspace->CameraRotation,
                Context.Workspace->FovDegrees,
                Context.Workspace->Aspect,
                Context.Workspace->Near,
                Context.Workspace->Far
            );
        }

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
            return std::nullopt;
        }

        return Rendering::Camera(
            Camera->Position,
            Camera->Rotation,
            Camera->FovDegrees,
            Camera->Aspect,
            Camera->Near,
            Camera->Far
        );
    }

    void RenderingModule::Render(const std::optional<Rendering::Camera>& ActiveCamera)
    {
        if (!ActiveCamera)
        {
            return;
        }

        Backend->Begin(*ActiveCamera);

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