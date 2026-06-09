#pragma once

#include "../Components/Transform.h"
#include "../Components/Spin.h"
#include "../Core/ECS/Registry.h"

namespace Core::Systems
{
    class SpinSystem
    {
    public:
        void Update(Core::ECS::Registry& World, float Dt)
        {
            World.View<Components::Transform, Components::Spin>(
                [Dt](Core::ECS::Entity, Components::Transform& T, Components::Spin& S)
                {
                    T.Rotation += S.Speed * Dt;
                }
            );
        }
    };
}
