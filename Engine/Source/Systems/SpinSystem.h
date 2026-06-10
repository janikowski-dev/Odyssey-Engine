#pragma once

#include "../Components/Transform.h"
#include "../Components/Spin.h"
#include "../Source/ECS/Registry.h"

namespace Source::Systems
{
    class SpinSystem
    {
    public:
        void Update(Source::ECS::Registry& World, float DeltaTime)
        {
            World.View<Components::Transform, Components::Spin>(
                [DeltaTime](Source::ECS::Entity, Components::Transform& T, Components::Spin& S)
                {
                    T.Rotation += S.Speed * DeltaTime;
                }
            );
        }
    };
}
