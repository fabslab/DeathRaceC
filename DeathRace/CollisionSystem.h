#pragma once

#include "ECS.h"
#include "raylib.h"
#include <utility>

class CollisionSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
    static bool PassesCollisionFilter(ECS::Entity* entity, ECS::Entity* oEntity);
    static bool AreColliding(ECS::Entity* entity, ECS::Entity* oEntity);
    static Rectangle GetCollisionBox(ECS::Entity* entity);
    static Rectangle GetCollisionBox(const Vector2& position, const float& width, const float& height);
};
