#include "Modules/WorkspaceModule.h"

namespace Source::Modules
{
    void WorkspaceModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitWorkspace(Config, Context);
        InitTime();
    }

    void WorkspaceModule::Tick(const Core::Context& Context)
    {
        RotateCamera(Context);
        MoveCamera(Context);
    }
    
    void WorkspaceModule::InitWorkspace(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.Workspace = MakeUnique<Core::Workspace>();
    }
    
    void WorkspaceModule::InitTime()
    {
        LastTime = Clock::now();
    }

    void WorkspaceModule::RotateCamera(const Core::Context& Context)
    {
        constexpr float Sensitivity = 0.2f;

        Context.Workspace->CameraRotation.y -= Context.Workspace->CameraXDelta * Sensitivity;
        Context.Workspace->CameraRotation.x -= Context.Workspace->CameraYDelta * Sensitivity;
        Context.Workspace->CameraRotation.x = std::clamp(Context.Workspace->CameraRotation.x, -87.5f, 87.5f);

        Context.Workspace->CameraXDelta = 0.0f;
        Context.Workspace->CameraYDelta = 0.0f;
    }

    void WorkspaceModule::MoveCamera(const Core::Context& Context)
    {
        int MoveMask = Context.Workspace->CameraMoveDirection;
        Time Now = Clock::now();
        float EditorDeltaTime = Duration(Now - LastTime).count();
        LastTime = Now;

        if (MoveMask == 0)
        {
            return;
        }

        float PitchRad = glm::radians(Context.Workspace->CameraRotation.x);
        float YawRad = glm::radians(Context.Workspace->CameraRotation.y);
        
        Vector3 Forward = glm::normalize(Vector3(-cosf(PitchRad) * sinf(YawRad), sinf(PitchRad), -cosf(PitchRad) * cosf(YawRad)));
        Vector3 WorldUp(0.0f, 1.0f, 0.0f);
        Vector3 Right = glm::normalize(glm::cross(Forward, WorldUp));
        Vector3 Up = glm::normalize(glm::cross(Right, Forward));

        Vector3 Direction(0.0f);

        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Forward)) Direction += Forward;
        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Back)) Direction -= Forward;
        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Right)) Direction += Right;
        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Left)) Direction -= Right;
        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Up)) Direction += Up;
        if (MoveMask & static_cast<int>(Core::Workspace::Direction::Down)) Direction -= Up;

        constexpr float MoveSpeed = 5.0f;

        if (glm::length(Direction) <= 0.0f)
        {
            return;
        }

        Context.Workspace->CameraPosition += glm::normalize(Direction) * MoveSpeed * EditorDeltaTime;
    }
}
