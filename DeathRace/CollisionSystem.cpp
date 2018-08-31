#include "CollisionSystem.h"
#include "Components.h"

void CollisionSystem::tick(ECS::World* world, float deltaTime)
{
}

Rectangle CollisionSystem::GetCollisionBox(ECS::Entity* entity)
{
    auto collisionComponent = entity->get<Components::CollisionComponent>();
    auto transformComponent = entity->get<Components::Transform2DComponent>();
    return GetCollisionBox(transformComponent->position, collisionComponent->width, collisionComponent->height);
}

Rectangle CollisionSystem::GetCollisionBox(Vector2 position, float width, float height)
{
    return Rectangle{
        position.x - width / 2,
        position.y - height / 2,
        width,
        height
    };
}
