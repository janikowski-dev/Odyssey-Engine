#pragma once

#include "../Components/MeshRenderer.h"
#include "../Components/Transform.h"
#include "../Core/ECS/Registry.h"
#include "../Rendering/Renderer.h"
#include "../Types.h"

#include <iostream>

namespace Core::Systems
{
    class RenderSystem
    {
    public:
        explicit RenderSystem(Rendering::Renderer& InRenderer) : Backend(InRenderer)
        {
	        Cube = MakeShared<Rendering::Mesh>(MakeCube());
        }

        void Update(Core::ECS::Registry& World)
        {
            Backend.Begin();

            World.View<Components::Transform, Components::MeshRenderer>(
                [&](Core::ECS::Entity, Components::Transform& T, Components::MeshRenderer& M)
                {
                    if (Cube)
                    {
                        Backend.DrawMesh(T.Matrix(), *Cube, M.Color);
                    }

                    std::cout << "test\n";
                }
            );

            Backend.End();
        }

    private:
        Rendering::Mesh MakeCube()
        {
            const glm::vec3 P[8] = {
                {-0.5f,-0.5f,-0.5f}, { 0.5f,-0.5f,-0.5f}, { 0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f,-0.5f},
                {-0.5f,-0.5f, 0.5f}, { 0.5f,-0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
            };

            struct Face
            {
                int a, b, c, d;
                glm::vec3 n;
            };

            const Face F[6] = {
                {4,5,6,7, { 0, 0, 1}}, {1,0,3,2, { 0, 0,-1}},
                {0,4,7,3, {-1, 0, 0}}, {5,1,2,6, { 1, 0, 0}},
                {3,7,6,2, { 0, 1, 0}}, {0,1,5,4, { 0,-1, 0}},
            };

            std::vector<Rendering::Vertex> Vertices;
            std::vector<uint32> Indices;

            for (const Face& f : F)
            {
                uint32 base = static_cast<uint32>(Vertices.size());
                Vertices.push_back({ P[f.a], f.n });
                Vertices.push_back({ P[f.b], f.n });
                Vertices.push_back({ P[f.c], f.n });
                Vertices.push_back({ P[f.d], f.n });
                Indices.insert(Indices.end(), { base, base + 1, base + 2, base, base + 2, base + 3 });
            }

            return Rendering::Mesh(Vertices, Indices);
        }

    private:
		SharedPtr<Rendering::Mesh> Cube;
        Rendering::Renderer& Backend;
    };
}
