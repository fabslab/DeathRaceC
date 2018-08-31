#pragma once

#include "ECS.h"
#include "raylib.h"

class CollisionSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
    static Rectangle GetCollisionBox(ECS::Entity* entity);
    static Rectangle GetCollisionBox(const Vector2& position, const float& width, const float& height);
};
