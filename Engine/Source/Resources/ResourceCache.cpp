#include "Resources/ResourceCache.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Source::Resources
{
    namespace
    {
        enum class Stage
        {
            None,
            Vertex,
            Fragment
        };

        Stage MarkerFor(const std::string& Line)
        {
            std::istringstream Tokens(Line);
            std::string Word;
            Tokens >> Word;

            if (Word == "#vertex")
            {
                return Stage::Vertex;
            }

            if (Word == "#fragment")
            {
                return Stage::Fragment;
            }

            return Stage::None;
        }

        std::optional<Rendering::Shader> LoadShader(const std::filesystem::path& File)
        {
            std::ifstream Stream(File);

            if (!Stream)
            {
                return std::nullopt;
            }

            std::ostringstream Sources[3];
            Stage Current = Stage::None;

            std::string Line;

            while (std::getline(Stream, Line))
            {
                Stage Marker = MarkerFor(Line);

                if (Marker != Stage::None)
                {
                    Current = Marker;
                    continue;
                }

                if (Current != Stage::None)
                {
                    Sources[static_cast<int>(Current)] << Line << '\n';
                }
            }

            const std::string Fragment = Sources[static_cast<int>(Stage::Fragment)].str();
            const std::string Vertex = Sources[static_cast<int>(Stage::Vertex)].str();

            if (Vertex.empty() || Fragment.empty())
            {
                return std::nullopt;
            }

            return Rendering::Shader(Vertex.c_str(), Fragment.c_str());
        }

        std::optional<Rendering::Mesh> LoadMesh(const std::filesystem::path& File)
        {
            Assimp::Importer Importer;

            const aiScene* Scene = Importer.ReadFile(
                File.string(),
                aiProcess_Triangulate |
                aiProcess_GenSmoothNormals |
                aiProcess_JoinIdenticalVertices |
                aiProcess_PreTransformVertices |
                aiProcess_SortByPType
            );

            if (!Scene || (Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !Scene->mRootNode)
            {
                return std::nullopt;
            }

            std::vector<Rendering::Vertex> Vertices;
            std::vector<uint32> Indices;

            for (unsigned int M = 0; M < Scene->mNumMeshes; ++M)
            {
                const aiMesh* SubMesh = Scene->mMeshes[M];

                const uint32 Base = static_cast<uint32>(Vertices.size());

                for (unsigned int V = 0; V < SubMesh->mNumVertices; ++V)
                {
                    Rendering::Vertex Out;

                    const aiVector3D& P = SubMesh->mVertices[V];
                    Out.Position = Vector3{ P.x, P.y, P.z };

                    if (SubMesh->HasNormals())
                    {
                        const aiVector3D& N = SubMesh->mNormals[V];
                        Out.Normal = Vector3{ N.x, N.y, N.z };
                    }
                    else
                    {
                        Out.Normal = Vector3{ 0.0f, 0.0f, 0.0f };
                    }

                    Vertices.push_back(Out);
                }

                for (unsigned int F = 0; F < SubMesh->mNumFaces; ++F)
                {
                    const aiFace& Face = SubMesh->mFaces[F];

                    if (Face.mNumIndices != 3)
                    {
                        continue;
                    }

                    for (unsigned int I = 0; I < Face.mNumIndices; ++I)
                    {
                        Indices.push_back(Base + Face.mIndices[I]);
                    }
                }
            }

            if (Vertices.empty() || Indices.empty())
            {
                return std::nullopt;
            }

            return Rendering::Mesh(Vertices, Indices);
        }

        using ShaderResolver = std::function<Rendering::Shader*(const std::string&)>;
 
        std::optional<Rendering::Material> LoadMaterial(const std::filesystem::path& File, const ShaderResolver& Resolve)
        {
            std::ifstream Stream(File);
        
            if (!Stream)
            {
                return std::nullopt;
            }
        
            Json Json;
        
            try
            {
                Stream >> Json;
            }
            catch(...)
            {
                return std::nullopt;
            }
        
            auto ShaderField = Json.find("shader");
        
            if (ShaderField == Json.end() || !ShaderField->is_string())
            {
                return std::nullopt;
            }
        
            Rendering::Shader* ShaderPtr = Resolve(ShaderField->get<std::string>());
        
            if (!ShaderPtr)
            {
                return std::nullopt;
            }
        
            Rendering::Material Out(ShaderPtr);
        
            if (auto Floats = Json.find("floats"); Floats != Json.end() && Floats->is_object())
            {
                for (const auto& [Name, Value] : Floats->items())
                {
                    if (Value.is_number())
                    {
                        Out.Set(Name.c_str(), Value.get<float>());
                    }
                }
            }
        
            if (auto Vectors = Json.find("vec3"); Vectors != Json.end() && Vectors->is_object())
            {
                for (const auto& [Name, Value] : Vectors->items())
                {
                    Vector3 Vec(Value[0].get<float>(), Value[1].get<float>(), Value[2].get<float>());
                    Out.Set(Name.c_str(), Vec);
                }
            }
        
            return Out;
        }
        
        std::optional<Rendering::Procedural> LoadProcedural(const std::filesystem::path& File)
        {
            std::ifstream Stream(File);
        
            if (!Stream)
            {
                return std::nullopt;
            }
        
            return Rendering::Procedural(6);
        }
    }

    ResourceCache::ResourceCache(const std::string& InProjectResourcesPath, const std::string& InEngineResourcesPath) : ProjectResourcesPath(InProjectResourcesPath), EngineResourcesPath(InEngineResourcesPath), Procedurals(&LoadProcedural), Shaders(&LoadShader), Meshes(&LoadMesh), Materials([this](const std::filesystem::path& File) { return LoadMaterial(File, [this](const std::string& Name) { return Shaders.Get(Name); }); })
    {
        Procedurals.SetExtensions({ ".proc" });
        Materials.SetExtensions({ ".mat" });
        Shaders.SetExtensions({ ".glsl" });
        Meshes.SetExtensions({ ".fbx" });
    }

    void ResourceCache::Refresh()
    {
        Meshes.Refresh(ProjectResourcesPath);
        Shaders.Refresh(ProjectResourcesPath);
        Materials.Refresh(ProjectResourcesPath);
        Procedurals.Refresh(ProjectResourcesPath);

        Meshes.Refresh(EngineResourcesPath);
        Shaders.Refresh(EngineResourcesPath);
        Materials.Refresh(EngineResourcesPath);
        Procedurals.Refresh(EngineResourcesPath);
    }
}