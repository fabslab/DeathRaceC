#pragma once

#include "ECS.h"

class AnimationSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
};
