#include "SystemsModule.h"

#include "../Messaging/MessageBus.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Mesh.h"
#include "../ECS/Registry.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Transform.h"
#include "../Components/Spin.h"

namespace Source::Modules
{
    SystemsModule::SystemsModule() = default;
    SystemsModule::~SystemsModule() = default;

    void SystemsModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitRendering();
        InitTime();
        InitSystems(Config, Context);
    }

    void SystemsModule::Tick(const Core::Context& Context)
    {
        HandleTime();
        UpdateSystems(Context);
    }

    void SystemsModule::InitRendering()
    {
        RendererBackend = MakeUnique<Rendering::Renderer>();
        RendererBackend->SetViewport(1280, 720);

        Rendering::Camera Camera;
        Camera.Position = { 4.0f, 3.0f, 6.0f };
        Camera.Target = { 0.0f, 0.0f, 0.0f };
        Camera.Up = { 0.0f, 1.0f, 0.0f };
        RendererBackend->SetCamera(Camera);

        Cube = MakeUnique<Rendering::Mesh>(MakeCube());
    }

    void SystemsModule::InitTime()
    {
        LastTime = Clock::now();
    }

    void SystemsModule::InitSystems(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();
    }

    void SystemsModule::HandleTime()
    {
        CurrentTime = Clock::now();
        DeltaTime = Duration(CurrentTime - LastTime).count();
        LastTime = CurrentTime;
    }

    void SystemsModule::UpdateSystems(const Core::Context& Context)
    {
        Context.World->View<Components::Transform, Components::Spin>(
            [this](Source::ECS::Entity, Components::Transform& T, Components::Spin& S)
            {
                T.Rotation += S.Speed * DeltaTime;
            }
        );

        RendererBackend->Begin();

        Context.World->View<Components::Transform, Components::MeshRenderer>(
            [this](Source::ECS::Entity, Components::Transform& T, Components::MeshRenderer& M)
            {
                if (Cube)
                {
                    RendererBackend->DrawMesh(T.Matrix(), *Cube, M.Color);
                }
            }
        );

        RendererBackend->End();
    }

    Rendering::Mesh SystemsModule::MakeCube()
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
}