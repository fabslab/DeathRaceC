#pragma once

#include "Components.h"
#include "ECS.h"

class EnemyMovementSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
    static bool IsCollisionAhead(ECS::World* world, ECS::Entity* entity);
    static bool ShouldMakeTimeBasedTurn(ECS::Entity* entity);
    static Vector2 GetRandomTurnDirection(ECS::Entity* entity);
    static void UpdateEnemyDirection(ECS::Entity* entity, Vector2 direction);
};
