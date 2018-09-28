#include "CollisionEventSubscriber.h"
#include "Components.h"
#include "EnemyMovementSystem.h"
#include "Entities.h"
#include "GameAudio.h"
#include "raylib.h"

void CollisionEventSubscriber::receive(ECS::World* world, const Events::CollisionEvent& event)
{
    auto firstEntity = event.firstEntity;
    auto secondEntity = event.secondEntity;
    auto playerMovementComponent = firstEntity->get<Components::PlayerMovementComponent>();
    if (playerMovementComponent) {
        if (secondEntity->get<Components::EnemyMovementComponent>()) {
            if (!EnemyMovementSystem::IsEnemySafe(world, secondEntity)) {
                KillEnemy(world, secondEntity, firstEntity);
            }
        } else {
            CrashPlayer(firstEntity);
        }
    }
}

void CollisionEventSubscriber::KillEnemy(ECS::World* world, ECS::Entity* enemy, ECS::Entity* player)
{
    PlaySound(GameAudio::scream);
    auto enemyTransformComponent = enemy->get<Components::Transform2DComponent>();
    Entities::CreateTombstone(world, enemyTransformComponent->position);
    EnemyMovementSystem::ResetEnemy(enemy);
    player->get<Components::ScoreComponent>()->score++;
}

void CollisionEventSubscriber::CrashPlayer(ECS::Entity* player)
{
    auto playerMovementComponent = player->get<Components::PlayerMovementComponent>();
    if (playerMovementComponent->remainingCrashTime <= 0.f) {
        PlaySound(GameAudio::collision);
        playerMovementComponent->remainingCrashTime = playerMovementComponent->crashTime;
    }
}
