#include "SerializationModule.h"

#include "../Platform/Window.h"
#include "../Serialization/ComponentRegistry.h"
#include "../Serialization/SceneSerializer.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Transform.h"
#include "../Components/Spin.h"

namespace Core::Modules
{
    SerializationModule::SerializationModule()
    {
        ComponentRegistry = MakeUnique<Serialization::ComponentRegistry>();
        ComponentRegistry->Register<Components::Transform>("Transform");
        ComponentRegistry->Register<Components::MeshRenderer>("Mesh");
        ComponentRegistry->Register<Components::Spin>("Spin");
    }

    void SerializationModule::Init(const ApplicationConfig Config, Context& Context)
    {
        Context.SceneSerializer = MakeUnique<Serialization::SceneSerializer>(*ComponentRegistry);
    }
}