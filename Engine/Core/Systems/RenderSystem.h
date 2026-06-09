#pragma once

#include "../Components/MeshRenderer.h"
#include "../Components/Transform.h"
#include "../Core/ECS/Registry.h"
#include "../Rendering/Renderer.h"

namespace Core::Systems
{
    class RenderSystem
    {
    public:
        explicit RenderSystem(Renderer::Renderer& InRenderer) : Backend(InRenderer) {}

        void Update(Core::ECS::Registry& World)
        {
            Backend.Begin();

            World.View<Components::Transform, Components::MeshRenderer>(
                [&](Core::ECS::Entity, Components::Transform& T, Components::MeshRenderer& M)
                {
                    if (M.Mesh)
                    {
                        Backend.DrawMesh(T.Matrix(), *M.Mesh, M.Color);
                    }
                }
            );

            Backend.End();
        }

    private:
        Renderer::Renderer& Backend;
    };
}
