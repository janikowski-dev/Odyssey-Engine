#pragma once

#include "Resources/ResourceLibrary.h"
#include "Rendering/Material.h"
#include "Rendering/Shader.h"
#include "Rendering/Drawables/Mesh.h"
#include "Core/Minimal.h"

namespace Source::Resources
{
    class ResourceCache
    {
    public:
        ResourceCache(const std::string& InPath);
        void Refresh();

    public:
        ResourceLibrary<Rendering::Material> Materials;
        ResourceLibrary<Rendering::Shader> Shaders;
        ResourceLibrary<Rendering::Mesh> Meshes;

    private:
        std::string Path;
    };
}