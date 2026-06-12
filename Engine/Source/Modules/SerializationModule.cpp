#include "SerializationModule.h"

#include "Serialization/SceneSerializer.h"
#include "Components/CameraComponent.h"
#include "Components/RendererComponent.h"
#include "Components/TransformComponent.h"
#include "Components/SpinComponent.h"

namespace Source::Modules
{
    SerializationModule::SerializationModule()
    {
    }

    void SerializationModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.SceneSerializer = MakeUnique<Serialization::SceneSerializer>();
    }
}