#include "SerializationModule.h"

#include "../Serialization/ComponentRegistry.h"
#include "../Serialization/SceneSerializer.h"
#include "../Components/CameraComponent.h"
#include "../Components/RendererComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpinComponent.h"

namespace Source::Modules
{
    SerializationModule::SerializationModule()
    {
        ComponentRegistry.Register<Components::TransformComponent>("Transform");
        ComponentRegistry.Register<Components::RendererComponent>("Renderer");
        ComponentRegistry.Register<Components::CameraComponent>("Camera");
        ComponentRegistry.Register<Components::SpinComponent>("Spin");
    }

    void SerializationModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.SceneSerializer = MakeUnique<Serialization::SceneSerializer>(ComponentRegistry);
    }
}