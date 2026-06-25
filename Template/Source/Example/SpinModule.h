#pragma once

#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Components/CameraComponent.h"
#include "Example/SpinComponent.h"
#include "Example/MoveComponent.h"
#include "Core/IModule.h"

namespace Game::Example
{
    class EXTERNAL_MODULE SpinModule : public Source::Core::IModule
    {
        Source::Core::TickPolicy GetTickPolicy() const override { return Source::Core::TickPolicy::Playtime; }

        void OnBeginPlay(const Source::Core::Context& Context) override
        {
            Source::ECS::Entity E = Context.World->Create();
            Context.World->Add<Source::Components::TransformComponent>(E, Source::Components::TransformComponent{ {-2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} });
            Context.World->Add<Source::Components::RendererComponent>(E, Source::Components::RendererComponent{ "Lit", "Prism", {0.85f, 0.30f, 0.22f} });
            Context.World->Add<MoveComponent>(E, MoveComponent{ {0.0f, 5.0f, 0.0f} });
            Context.World->Add<SpinComponent>(E, SpinComponent{ {0.0f, 50.0f, 0.0f} });
            Entities.push_back(E);
        }

        void OnEndPlay(const Source::Core::Context& Context) override
        {
            for(auto& Entity : Entities)
            {
                Context.World->Destroy(Entity);
            }

            Entities.clear();
        }

    	void Tick(const Source::Core::Context& Context) override
        {
            Context.World->View<Source::Components::TransformComponent, MoveComponent>(
                [&Context](Source::ECS::Entity, Source::Components::TransformComponent& T, MoveComponent& M)
                {
                    if (Context.Input->IsPressed(Source::Platform::Key::W))
                    {
                        T.Position += Context.Time->DeltaTime * M.Speed;
                    }
                    
                    if (Context.Input->IsPressed(Source::Platform::Key::S))
                    {
                        T.Position -= Context.Time->DeltaTime * M.Speed;
                    }
                }
            );

            Context.World->View<Source::Components::TransformComponent, SpinComponent>(
                [&Context](Source::ECS::Entity, Source::Components::TransformComponent& T, SpinComponent& S)
                {
                    T.Rotation += S.Speed * Context.Time->DeltaTime;
                }
            );
        }

        std::vector<Source::ECS::Entity> Entities;
    };
}