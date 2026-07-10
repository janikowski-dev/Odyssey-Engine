#pragma once

#include "Rendering/Drawables/Procedural.h"
#include "Resources/ResourceLibrary.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Material.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Core/Minimal.h"

namespace Source::Resources
{
    class ResourceCache
    {
    public:
        ResourceCache();
        
        void Refresh(const std::string& Path);

    public:
        ResourceLibrary<Rendering::Procedural> Procedurals;
        ResourceLibrary<Rendering::Material> Materials;
        ResourceLibrary<Rendering::Texture> Textures;
        ResourceLibrary<Rendering::Shader> Shaders;
        ResourceLibrary<Rendering::Mesh> Meshes;
    };
}