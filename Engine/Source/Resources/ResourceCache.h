#pragma once

#include "ResourceLibrary.h"

#include "../Core/Types.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Mesh.h"

namespace Source::Resources
{
    class ResourceCache
    {
    public:
        ResourceLibrary<Rendering::Shader> Shaders;
        ResourceLibrary<Rendering::Mesh> Meshes;
    };
}