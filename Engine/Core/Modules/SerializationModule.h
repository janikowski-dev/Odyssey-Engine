#pragma once

#include "../IModule.h"
#include "../Platform/Window.h"

#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Spin.h"

namespace Core
{
    class SerializationModule final : public IModule
    {
    public:
        SerializationModule()
        {
		    ComponentRegistry = MakeUnique<Serialization::ComponentRegistry>();
		    ComponentRegistry->Register<Components::Transform>("Transform");
		    ComponentRegistry->Register<Components::MeshRenderer>("Mesh");
		    ComponentRegistry->Register<Components::Spin>("Spin");
        }

        ~SerializationModule() override = default;

        void Init(const ApplicationConfig Config, Context& Context) override
        {
		    Context.SceneSerializer = MakeUnique<Serialization::SceneSerializer>(*ComponentRegistry);
        }

    private:
		UniquePtr<Serialization::ComponentRegistry> ComponentRegistry;
    };
}