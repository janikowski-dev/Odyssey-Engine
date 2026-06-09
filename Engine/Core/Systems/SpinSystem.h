#pragma once

#include "../Components/Transform.h"
#include "../Components/Spin.h"
#include "../Core/ECS/Registry.h"

namespace Core::Systems
{
    class SpinSystem
    {
    public:
        void Update(Core::ECS::Registry& World, float DeltaTime)
        {
            World.View<Components::Transform, Components::Spin>(
                [DeltaTime](Core::ECS::Entity, Components::Transform& T, Components::Spin& S)
                {
                    T.Rotation += S.Speed * DeltaTime;
                }
            );
        }
    };
}
