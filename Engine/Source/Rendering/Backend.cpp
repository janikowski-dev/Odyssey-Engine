#include "Rendering/Backend.h"

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/Drawables/Mesh.h"
#include "Rendering/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/Material.h"
#include "Rendering/Camera.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    void Backend::Begin(const Camera& InCamera)
    {
        Cache(InCamera);
        Begin();
    }

    void Backend::Begin()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0.10f, 0.11f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Backend::End()
    {
        glUseProgram(0);
    }

    void Backend::Draw(const Transform& InTransform, const Renderer& InRenderer)
    {
        InRenderer.MaterialPtr->Bind();
        InRenderer.MaterialPtr->Use();
        InRenderer.MaterialPtr->SetSoft("uModel", InTransform.Matrix);
        InRenderer.MaterialPtr->SetSoft("uProj", Projection);
        InRenderer.MaterialPtr->SetSoft("uView", View);
        InRenderer.DrawablePtr->Draw();
    }

    void Backend::Draw(const Renderer& InRenderer)
    {
        InRenderer.MaterialPtr->Bind();
        InRenderer.MaterialPtr->Use();
        InRenderer.MaterialPtr->SetSoft("uProj", Projection);
        InRenderer.MaterialPtr->SetSoft("uView", View);
        InRenderer.DrawablePtr->Draw();
    }

    void Backend::Cache(const Camera& InCamera)
    {
        Projection = InCamera.Projection;
        View = InCamera.View;
    }
}
