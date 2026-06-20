#include "Entities.h"
#include "Components.h"
#include "GameBalance.h"
#include "Textures.h"

void Entities::CreateEnemy(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(
        Balance::ENEMY_COLLISION_WIDTH,
        Balance::ENEMY_COLLISION_HEIGHT,
        false,
        CollisionLayer::Enemy,
        ~(CollisionLayer::Sidewalk | CollisionLayer::Enemy));
    entity->assign<Components::EnemyMovementComponent>(
        position,
        Balance::ENEMY_SPEED,
        Balance::ENEMY_TURN_TIME_MIN_MS,
        Balance::ENEMY_TURN_TIME_MAX_MS,
        Balance::ENEMY_TURN_CHANCE);
    entity->assign<Components::TextureAnimationComponent>(
        Balance::ENEMY_ANIMATION_FRAMES,
        Balance::ENEMY_ANIMATION_FRAME_DURATION_MS);
    entity->assign<Components::TextureComponent>(Textures::enemyFront, Color(WHITE), Rectangle { 0.f, 0.f, 16.f, 16.f });
    entity->assign<Components::Transform2DComponent>(position);
}

void Entities::CreatePlayer(ECS::World* world, PlayerIndex playerIndex, Vector2 position, Color color)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(
        Balance::PLAYER_COLLISION_WIDTH,
        Balance::PLAYER_COLLISION_HEIGHT,
        false,
        CollisionLayer::Player,
        CollisionLayer::All);
    entity->assign<Components::PlayerMovementComponent>(
        playerIndex,
        Balance::PLAYER_FORWARD_SPEED,
        Balance::PLAYER_REVERSE_SPEED,
        Balance::PLAYER_SPEED_WHILE_COLLIDING,
        Balance::PLAYER_CRASH_DURATION_MS);
    entity->assign<Components::ScoreComponent>(playerIndex);
    entity->assign<Components::SnappedRotationComponent>(
        Balance::PLAYER_MAX_TURN_ANGLE_PER_UPDATE,
        Balance::PLAYER_SNAP_ANGLE);
    entity->assign<Components::TextureComponent>(Textures::player, color);
    entity->assign<Components::Transform2DComponent>(position, PI);
}

void Entities::CreateTombstone(ECS::World* world, Vector2 position)
{
    auto entity = world->create();
    entity->assign<Components::CollisionComponent>(
        Balance::TOMBSTONE_COLLISION_WIDTH,
        Balance::TOMBSTONE_COLLISION_HEIGHT,
        true,
        CollisionLayer::Tombstone,
        CollisionLayer::All);
    entity->assign<Components::TextureComponent>(Textures::tombstone);
    entity->assign<Components::Transform2DComponent>(position);
}
