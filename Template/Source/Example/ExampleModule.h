#pragma once

#include "Components/CameraComponent.h"
#include "Core/IModule.h"

#include "Example/ExampleComponent.h"

namespace Game::Example
{
    class EXTERNAL_MODULE ExampleModule : public Source::Core::IModule
    {
        virtual void Init(const Source::Core::ApplicationConfig Config, Source::Core::Context& Context) override
        {
            Source::ECS::Entity E = Context.World->Create();
            Context.World->Add<Source::Components::CameraComponent>(E, Source::Components::CameraComponent{ {4.0f, 3.0f, 6.0f} });
            Context.World->Add<ExampleComponent>(E, ExampleComponent());
        }

    	virtual void Tick(const Source::Core::Context& Context) override
        {
            Context.World->View<ExampleComponent>(
                [this](Source::ECS::Entity E, ExampleComponent&)
                {
                    DebugLog << E.Index;
                }
            );
        }
    };
}