#include "EnemyMovementSystem.h"
#include "MathUtil.h"
#include "Textures.h"
#include "raymath.h"

void EnemyMovementSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<
        Components::Transform2DComponent,
        Components::TextureComponent,
        Components::TextureAnimationComponent,
        Components::EnemyMovementComponent>(
        [&](
            ECS::Entity* entity,
            ECS::ComponentHandle<Components::Transform2DComponent> transformComponent,
            ECS::ComponentHandle<Components::TextureComponent> textureComponent,
            ECS::ComponentHandle<Components::TextureAnimationComponent> animationComponent,
            ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent) {
            movementComponent->timeSinceTurn += deltaTime;
            if (ShouldMakeTurn(movementComponent)) {
                movementComponent->direction = GetTurnDirection(movementComponent);
                UpdateSpriteDirection(textureComponent, animationComponent, movementComponent->direction);
                movementComponent->timeSinceTurn = 0.f;
            }
            Vector3 movement = Vector3Scale(movementComponent->direction, movementComponent->speed);
            transformComponent->position = Vector2Add(
                transformComponent->position,
                Vector2{ movement.x, movement.y });
        });
}

bool EnemyMovementSystem::ShouldMakeTurn(
    ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent)
{
    bool shouldTurn = false;
    if (movementComponent->timeSinceTurn >= movementComponent->timeRangeEnd) {
        shouldTurn = true;
    } else if (movementComponent->timeSinceTurn >= movementComponent->timeRangeStart) {
        shouldTurn = GetRandomValue(0, 99) < (movementComponent->chancePerUpdate * 100);
    }
    return shouldTurn;
}

Vector3 EnemyMovementSystem::GetTurnDirection(
    ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent)
{
    // 50/50 chance to turn left/right
    Vector3 turnDirection = Vector3CrossProduct(movementComponent->direction, { 0, 0, 1 });
    if (GetRandomValue(0, 1) == 0) {
        turnDirection = { -turnDirection.x, -turnDirection.y, 0 };
    }
    return turnDirection;
}

void EnemyMovementSystem::UpdateSpriteDirection(
    ECS::ComponentHandle<Components::TextureComponent> textureComponent,
    ECS::ComponentHandle<Components::TextureAnimationComponent> animationComponent,
    Vector3 direction)
{
    if (direction == DirectionVectors::Left) {
        textureComponent->texture = Textures::enemyLeft;
    } else if (direction == DirectionVectors::Right) {
        textureComponent->texture = Textures::enemyRight;
    } else {
        textureComponent->texture = Textures::enemyFront;
    }
    animationComponent->currentFrameIndex = 0;
    animationComponent->remainingFrameTime = 0.f;
}
