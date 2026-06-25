#pragma once

#include "Resources/ResourceLibrary.h"
#include "Rendering/Shader.h"
#include "Rendering/Mesh.h"
#include "Core/Minimal.h"

namespace Source::Resources
{
    class ResourceCache
    {
    public:
        ResourceCache(const std::string& InPath);
        void Refresh();

    public:
        ResourceLibrary<Rendering::Shader> Shaders;
        ResourceLibrary<Rendering::Mesh> Meshes;

    private:
        std::string Path;
    };
}