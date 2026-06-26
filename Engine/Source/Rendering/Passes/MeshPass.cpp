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

#include <glm/gtc/matrix_transform.hpp>

namespace Source::Rendering
{
    MeshPass::MeshPass(Core::Context& InContext) : ContextPtr(&InContext)
    {
    }

    void MeshPass::Execute(Backend& InBackend)
    {
        ContextPtr->World->View<Components::TransformComponent, Components::RendererComponent>(
            [&InBackend, this](ECS::Entity, Components::TransformComponent& T, Components::RendererComponent& R)
            {
                const auto Material = ContextPtr->ResourceCache->Materials.Get(R.MaterialId);

                if (!Material)
                {
                    return;
                }

                const auto Mesh = ContextPtr->ResourceCache->Meshes.Get(R.MeshId);

                if (!Mesh)
                {
                    return;
                }
                
                InBackend.Draw(Rendering::Transform(T.Position, T.Rotation, T.Scale), Rendering::Renderer(Material, Mesh));
            }
        );
    }
}
