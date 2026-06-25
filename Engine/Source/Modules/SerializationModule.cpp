#include "Modules/SerializationModule.h"

#include "Serialization/SceneSerializer.h"

#include "Serialization.generated.h"

namespace Source::Modules
{
    void SerializationModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Serialization::Init(*Context.World);
        Serialization::LoadScene(*Context.World, Config.EngineConfig.GetScenePath());
    }

    void SerializationModule::OnBeginPlay(const Core::Context &Context)
    {
        Serialization::SerializeScene(*Context.World, EditorScene);
    }

    void SerializationModule::OnEndPlay(const Core::Context &Context)
    {
        Serialization::DeserializeScene(*Context.World, EditorScene);
    }
}
