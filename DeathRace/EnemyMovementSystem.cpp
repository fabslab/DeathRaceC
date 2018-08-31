#include "EnemyMovementSystem.h"
#include "CollisionSystem.h"
#include "MathUtil.h"
#include "Textures.h"
#include "raymath.h"

void EnemyMovementSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<
        Components::Transform2DComponent,
        Components::EnemyMovementComponent>(
        [&](
            ECS::Entity* entity,
            ECS::ComponentHandle<Components::Transform2DComponent> transformComponent,
            ECS::ComponentHandle<Components::EnemyMovementComponent> movementComponent) {
            movementComponent->timeSinceTurn += deltaTime;
            bool madeTurn = false;
            bool stuck = false;
            Vector3 originalDirection = movementComponent->direction;
            if (IsCollisionAhead(world, entity)) {
                // Try random left/right turn
                UpdateEnemyDirection(entity, GetRandomTurnDirection(entity));
                madeTurn = true;
                if (IsCollisionAhead(world, entity)) {
                    // Try opposite turn
                    UpdateEnemyDirection(entity, Vector3Negate(movementComponent->direction));
                    if (IsCollisionAhead(world, entity)) {
                        // Turn entity around from original movement direction
                        UpdateEnemyDirection(entity, Vector3Negate(originalDirection));
                        if (IsCollisionAhead(world, entity)) {
                            UpdateEnemyDirection(entity, originalDirection);
                            stuck = true;
                        }
                    }
                }
            }
            if (!stuck) {
                if (!madeTurn && ShouldMakeTimeBasedTurn(entity)) {
                    UpdateEnemyDirection(entity, GetRandomTurnDirection(entity));
                }
                Vector3 movement = Vector3Scale(movementComponent->direction, movementComponent->speed);
                transformComponent->position = Vector2Add(
                    transformComponent->position,
                    Vector2{ movement.x, movement.y });
            }
        });
}

bool EnemyMovementSystem::IsCollisionAhead(ECS::World* world, ECS::Entity* entity)
{
    auto movementComponent = entity->get<Components::EnemyMovementComponent>();
    auto transformComponent = entity->get<Components::Transform2DComponent>();
    auto collisionComponent = entity->get<Components::CollisionComponent>();
    // Should cast the collision box but instead we simply shift it by the look distance
    Vector3 lookAmount = Vector3Scale(movementComponent->direction, movementComponent->lookDistance);
    Vector2 lookAheadPoint = Vector2Add(transformComponent->position, Vector2{ lookAmount.x, lookAmount.y });
    Rectangle collisionBox = CollisionSystem::GetCollisionBox(lookAheadPoint, collisionComponent->width, collisionComponent->height);
    for (auto otherCollisionEntity : world->each<Components::CollisionComponent, Components::Transform2DComponent>()) {
        if (otherCollisionEntity != entity) {
            // TODO: Add collision filter check, call into collision system to do it
            Rectangle otherCollisionBox = CollisionSystem::GetCollisionBox(otherCollisionEntity);
            if (CheckCollisionRecs(collisionBox, otherCollisionBox)) {
                return true;
            }
        }
    }
    return false;
}

bool EnemyMovementSystem::ShouldMakeTimeBasedTurn(ECS::Entity* entity)
{
    auto movementComponent = entity->get<Components::EnemyMovementComponent>();
    bool shouldTurn = false;
    if (movementComponent->timeSinceTurn >= movementComponent->timeRangeEnd) {
        shouldTurn = true;
    } else if (movementComponent->timeSinceTurn >= movementComponent->timeRangeStart) {
        shouldTurn = GetRandomValue(0, 99) < (movementComponent->chancePerUpdate * 100);
    }
    return shouldTurn;
}

Vector3 EnemyMovementSystem::GetRandomTurnDirection(ECS::Entity* entity)
{
    auto movementComponent = entity->get<Components::EnemyMovementComponent>();
    // 50/50 chance to turn left/right
    Vector3 turnDirection = Vector3CrossProduct(movementComponent->direction, { 0, 0, 1 });
    if (GetRandomValue(0, 1) == 0) {
        turnDirection = { -turnDirection.x, -turnDirection.y, 0 };
    }
    return turnDirection;
}

void EnemyMovementSystem::UpdateEnemyDirection(ECS::Entity* entity, Vector3 direction)
{
    auto textureComponent = entity->get<Components::TextureComponent>();
    auto animationComponent = entity->get<Components::TextureAnimationComponent>();
    auto movementComponent = entity->get<Components::EnemyMovementComponent>();
    movementComponent->direction = direction;
    if (direction == DirectionVectors::Left) {
        textureComponent->texture = Textures::enemyLeft;
    } else if (direction == DirectionVectors::Right) {
        textureComponent->texture = Textures::enemyRight;
    } else {
        textureComponent->texture = Textures::enemyFront;
    }
    animationComponent->currentFrameIndex = 0;
    animationComponent->remainingFrameTime = 0.f;
    movementComponent->timeSinceTurn = 0.f;
}
