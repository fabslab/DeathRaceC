#pragma once

#include "ECS.h"

class RenderSystem : public ECS::EntitySystem {
public:
    void tick(ECS::World* world, float deltaTime) override;
};
