#include "Entities.h"
#include "Components.h"
#include "Textures.h"

void Entities::CreateEnemy(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::Transform2DComponent>(position);
    entity->assign<Components::TextureComponent>(Textures::enemyFront, Color(WHITE), Rectangle{ 0.f, 0.f, 16.f, 16.f });
    entity->assign<Components::TextureAnimationComponent>(2, 60.f);
    entity->assign<Components::EnemyMovementComponent>(position, 1.5f, 350.f, 1800.f, .05);
    entity->assign<Components::CollisionComponent>(14, 15, false, CollisionLayer::Enemy, ~CollisionLayer::Sidewalk);
}

void Entities::CreatePlayer(ECS::World* world, int playerIndex, Vector2 position, Color color)
{
    auto entity = world->create();
    entity->assign<Components::Transform2DComponent>(position, PI);
    entity->assign<Components::TextureComponent>(Textures::player, color);
    entity->assign<Components::SnappedRotationComponent>();
    entity->assign<Components::PlayerMovementComponent>(playerIndex, 2.f, 1.f);
    entity->assign<Components::CollisionComponent>(12, 16, false, CollisionLayer::Player, CollisionLayer::All);
}

void Entities::CreateTombstone(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::Transform2DComponent>(position);
    entity->assign<Components::TextureComponent>(Textures::tombstone);
    entity->assign<Components::CollisionComponent>(9, 14, true, CollisionLayer::Tombstone, CollisionLayer::All);
}
