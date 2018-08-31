#pragma once

#include "ECS.h"
#include "raylib.h"

class CollisionSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
    static Rectangle GetCollisionBox(ECS::Entity* entity);
    static Rectangle GetCollisionBox(Vector2 position, float width, float height);
};
