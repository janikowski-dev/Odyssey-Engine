#include "Modules/ResourcesModule.h"

#include "Resources/ResourceCache.h"

namespace Source::Modules
{
    // === Temporary ===
    namespace
    {
        const char* DefaultVertex = R"(#version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;
            
        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProj;
            
        out vec3 vNormal;
            
        void main()
        {
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;
            gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
        }
        )";

        const char* DefaultFragment = R"(#version 330 core
        in vec3 vNormal;
        uniform vec3 uColor;
        out vec4 FragColor;

        void main()
        {
            vec3 N = normalize(vNormal);
            vec3 L = normalize(vec3(0.4, 1.0, 0.6));
            float diff = max(dot(N, L), 0.0);
            vec3 c = uColor * (0.25 + 0.75 * diff);
            FragColor = vec4(c, 1.0);
        }
        )";
    }

    Rendering::Mesh MakeCube()
    {
        const Vector3 P[8] = {
            {-0.5f,-0.5f,-0.5f}, { 0.5f,-0.5f,-0.5f}, { 0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f,-0.5f},
            {-0.5f,-0.5f, 0.5f}, { 0.5f,-0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
        };

        struct Face
        {
            int A, B, C, D;
            Vector3 N;
        };

        const Face Faces[6] = {
            {4,5,6,7, { 0, 0, 1}}, {1,0,3,2, { 0, 0,-1}},
            {0,4,7,3, {-1, 0, 0}}, {5,1,2,6, { 1, 0, 0}},
            {3,7,6,2, { 0, 1, 0}}, {0,1,5,4, { 0,-1, 0}},
        };

        std::vector<Rendering::Vertex> Vertices;
        std::vector<uint32> Indices;

        for (const Face& Face : Faces)
        {
            uint32 Base = static_cast<uint32>(Vertices.size());
            Vertices.push_back({ P[Face.A], Face.N });
            Vertices.push_back({ P[Face.B], Face.N });
            Vertices.push_back({ P[Face.C], Face.N });
            Vertices.push_back({ P[Face.D], Face.N });
            Indices.insert(Indices.end(), { Base, Base + 1, Base + 2, Base, Base + 2, Base + 3 });
        }

        return Rendering::Mesh(Vertices, Indices);
    }
    // === Temporary ===

    void ResourcesModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.ResourceCache = MakeUnique<Resources::ResourceCache>();
        Context.ResourceCache->Shaders.Add("lit", Rendering::Shader(DefaultVertex, DefaultFragment));
        Context.ResourceCache->Meshes.Add("cube", MakeCube());
    }
}