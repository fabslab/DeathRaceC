#include "Enemy.h"
#include "Components.h"
#include "Textures.h"

Enemy::Enemy(ECS::Entity* entity, Vector2 position)
{
    entity->assign<Components::Transform2DComponent>(position);
    entity->assign<Components::TextureComponent>(Textures::enemyFront, Color(WHITE), Rectangle{ 0.f, 0.f, 16.f, 16.f });
    entity->assign<Components::TextureAnimationComponent>(2, 60.f);
    entity->assign<Components::EnemyMovementComponent>(1.5f, 350.f, 1800.f, .05);
    entity->assign<Components::CollisionComponent>(14, 15, CollisionLayer::Enemy, CollisionLayer::Player);
}
