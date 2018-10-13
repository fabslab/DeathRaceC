#include "Entities.h"
#include "Components.h"
#include "Textures.h"

void Entities::CreateEnemy(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(14, 15, false, CollisionLayer::Enemy, ~CollisionLayer::Sidewalk);
    entity->assign<Components::EnemyMovementComponent>(position, 1.5f, 350.f, 1800.f, .05);
    entity->assign<Components::TextureAnimationComponent>(2, 60.f);
    entity->assign<Components::TextureComponent>(Textures::enemyFront, Color(WHITE), Rectangle { 0.f, 0.f, 16.f, 16.f });
    entity->assign<Components::Transform2DComponent>(position);
}

void Entities::CreatePlayer(ECS::World* world, PlayerIndex playerIndex, Vector2 position, Color color)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(12, 16, false, CollisionLayer::Player, CollisionLayer::All);
    entity->assign<Components::PlayerMovementComponent>(playerIndex, 2.f, 1.f, .5f, 1000.f);
    entity->assign<Components::ScoreComponent>(playerIndex);
    entity->assign<Components::SnappedRotationComponent>(PI / 48, PI / 8);
    entity->assign<Components::TextureComponent>(Textures::player, color);
    entity->assign<Components::Transform2DComponent>(position, PI);
}

void Entities::CreateTombstone(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(9, 14, true, CollisionLayer::Tombstone, CollisionLayer::All);
    entity->assign<Components::TextureComponent>(Textures::tombstone);
    entity->assign<Components::Transform2DComponent>(position);
}
