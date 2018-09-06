#include "CollisionEventSubscriber.h"
#include "Components.h"
#include "EnemyMovementSystem.h"
#include "Entities.h"

void CollisionEventSubscriber::receive(ECS::World* world, const Events::CollisionEvent& event)
{
    auto firstEntity = event.firstEntity;
    auto secondEntity = event.secondEntity;

    auto playerMovementComponent = firstEntity->get<Components::PlayerMovementComponent>();
    if (playerMovementComponent) {
        if (secondEntity->get<Components::EnemyMovementComponent>()) {
            // increase score for player
        } else {
            // crash player
            if (playerMovementComponent->remainingCrashTime <= 0.f) {
                playerMovementComponent->remainingCrashTime = playerMovementComponent->crashTime;
            }
        }
    } else {
        auto enemyMovementComponent = firstEntity->get<Components::EnemyMovementComponent>();
        auto enemyTransformComponent = firstEntity->get<Components::Transform2DComponent>();
        if (enemyMovementComponent) {
            if (secondEntity->get<Components::PlayerMovementComponent>()) {
                Entities::CreateTombstone(world, enemyTransformComponent->position);
                EnemyMovementSystem::ResetEnemy(firstEntity);
            }
        }
    }
}
