#include "Rendering/Passes/SelectionPass.h"

#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/Material.h"
#include "Rendering/Backend.h"
#include "Core/Context.h"
#include "ECS/Registry.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    SelectionPass::SelectionPass(Core::Context& InContext) : ContextPtr(&InContext), MaterialPtr(InContext.ResourceCache->Materials.Get("Outline"))
    {
    }

    SelectionPass::~SelectionPass() = default;

    void SelectionPass::Execute(Backend& InBackend)
    {
        const ECS::Entity SelectedEntity(ContextPtr->Workspace->SelectedIndex);

        if (!ContextPtr->World->Has<Components::TransformComponent>(SelectedEntity))
        {
            return;
        }

        if (!ContextPtr->World->Has<Components::RendererComponent>(SelectedEntity))
        {
            return;
        }

        const Components::TransformComponent T = ContextPtr->World->Get<Components::TransformComponent>(SelectedEntity);
        const Components::RendererComponent R = ContextPtr->World->Get<Components::RendererComponent>(SelectedEntity);
        
        const auto MeshPtr = ContextPtr->ResourceCache->Meshes.Get(R.MeshId);

        if (!MeshPtr)
        {
            return;
        }
        
        glCullFace(GL_FRONT);
        InBackend.Draw(Rendering::Transform(T.Position, T.Rotation, T.Scale), Rendering::Renderer(MaterialPtr, MeshPtr));
        glCullFace(GL_BACK);
    }
}
