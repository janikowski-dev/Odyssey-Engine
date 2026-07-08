#pragma once

#include "Rendering/Drawables/Procedural.h"
#include "Resources/ResourceLibrary.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Material.h"
#include "Rendering/Shader.h"
#include "Core/Minimal.h"

namespace Source::Resources
{
    class ResourceCache
    {
    public:
        ResourceCache(const std::string& InLocalPath, const std::string& InGlobalPath);
        void Refresh();

    public:
        ResourceLibrary<Rendering::Procedural> Procedurals;
        ResourceLibrary<Rendering::Material> Materials;
        ResourceLibrary<Rendering::Shader> Shaders;
        ResourceLibrary<Rendering::Mesh> Meshes;

    private:
        std::string ProjectResourcesPath;
        std::string EngineResourcesPath;
    };
}