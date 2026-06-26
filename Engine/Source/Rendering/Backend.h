#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Transform;
    class Renderer;
    class Camera;

    class Backend
    {
    public:
        void Begin(const Camera& InCamera);
        void Draw(const Transform& InTransform, const Renderer& InRenderer);
        void Draw(const Renderer& InRenderer);
        void End();

    private:
        void Cache(const Camera& InCamera);
        void Begin();

    private:
        Matrix4 Projection { 1.0f };
        Matrix4 View { 1.0f };
    };
}
