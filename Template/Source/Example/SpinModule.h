#pragma once

#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Components/CameraComponent.h"
#include "Example/SpinComponent.h"
#include "Core/IModule.h"

namespace Game::Example
{
    class EXTERNAL_MODULE SpinModule : public Source::Core::IModule
    {
        virtual void Init(const Source::Core::ApplicationConfig Config, Source::Core::Context& Context) override
        {
            Source::ECS::Entity E1 = Context.World->Create();
            Context.World->Add<Source::Components::CameraComponent>(E1, Source::Components::CameraComponent{ {4.0f, 3.0f, 6.0f} });
            
            Source::ECS::Entity E2 = Context.World->Create();
            Context.World->Add<Source::Components::TransformComponent>(E2, Source::Components::TransformComponent{ {-2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} });
            Context.World->Add<Source::Components::RendererComponent>(E2, Source::Components::RendererComponent{ "lit", "cube", {0.85f, 0.30f, 0.22f}, Context.ResourceCache->Shaders.Get("lit"), Context.ResourceCache->Meshes.Get("cube") });
            Context.World->Add<SpinComponent>(E2, SpinComponent{ {0.0f, 0.8f, 0.0f} });
        }

    	virtual void Tick(const Source::Core::Context& Context) override
        {
            Context.World->View<Source::Components::TransformComponent, SpinComponent>(
                [&Context](Source::ECS::Entity, Source::Components::TransformComponent& T, SpinComponent& S)
                {
                    T.Rotation += S.Speed * Context.Runtimer->DeltaTime;
                }
            );
        }
    };
}