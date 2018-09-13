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
            if (!EnemyMovementSystem::IsEnemySafe(world, secondEntity)) {
                auto enemyTransformComponent = secondEntity->get<Components::Transform2DComponent>();
                Entities::CreateTombstone(world, enemyTransformComponent->position);
                EnemyMovementSystem::ResetEnemy(secondEntity);
                firstEntity->get<Components::ScoreComponent>()->score++;
            }
        } else {
            if (playerMovementComponent->remainingCrashTime <= 0.f) {
                playerMovementComponent->remainingCrashTime = playerMovementComponent->crashTime;
            }
        }
    }
}
