#include "Rendering/Passes/MeshPass.h"

#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/Material.h"
#include "Rendering/Backend.h"
#include "Core/Context.h"
#include "ECS/Registry.h"

namespace Source::Rendering
{
    MeshPass::MeshPass(Core::Context& InContext) : ContextPtr(&InContext)
    {
    }

    MeshPass::~MeshPass() = default;

    void MeshPass::Execute(Backend& InBackend)
    {
        auto ResourcesPtr = ContextPtr->ResourceCache.get();
        auto WorldPtr = ContextPtr->World.get();

        WorldPtr->View<Components::TransformComponent, Components::RendererComponent>(
            [&InBackend, ResourcesPtr](ECS::Entity, Components::TransformComponent& T, Components::RendererComponent& R)
            {
                const auto Material = ResourcesPtr->Materials.Get(R.MaterialId);

                if (!Material)
                {
                    return;
                }

                const auto Mesh = ResourcesPtr->Meshes.Get(R.MeshId);

                if (!Mesh)
                {
                    return;
                }
                
                InBackend.Draw(Rendering::Transform(T.Position, T.Rotation, T.Scale), Rendering::Renderer(Material, Mesh));
            }
        );
    }
}
