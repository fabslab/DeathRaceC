#pragma once

#include "Components.h"
#include "ECS.h"

class EnemyMovementSystem : public ECS::EntitySystem {
public:
    virtual void tick(ECS::World* world, float deltaTime) override;
    bool ShouldMakeTurn(ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent);
    Vector3 GetTurnDirection(ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent);
    void UpdateSpriteDirection(ECS::ComponentHandle<Components::TextureComponent> textureComponent, ECS::ComponentHandle<Components::TextureAnimationComponent> animationComponent, Vector3 direction);
};
