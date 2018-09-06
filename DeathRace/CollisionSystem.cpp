#include "CollisionSystem.h"
#include "Components.h"
#include "Events.h"

void CollisionSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<Components::CollisionComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::CollisionComponent> collisionComponent) {
            if (!collisionComponent->isStatic) {
                world->each<Components::CollisionComponent>(
                    [&](ECS::Entity* oEntity,
                        ECS::ComponentHandle<Components::CollisionComponent> oCollisionComponent) {
                        if (PassesCollisionFilter(entity, oEntity) && AreColliding(entity, oEntity)) {
                            world->emit(Events::CollisionEvent{ entity, oEntity });
                        }
                    });
            }
        });
}

bool CollisionSystem::PassesCollisionFilter(ECS::Entity* entity, ECS::Entity* oEntity)
{
    auto collisionComponent = entity->get<Components::CollisionComponent>();
    auto oCollisionComponent = oEntity->get<Components::CollisionComponent>();
    return entity != oEntity
        && (collisionComponent->layer & oCollisionComponent->filter) != CollisionLayer::None
        && (collisionComponent->filter & oCollisionComponent->layer) != CollisionLayer::None;
}

bool CollisionSystem::AreColliding(ECS::Entity* entity, ECS::Entity* oEntity)
{
    return CheckCollisionRecs(GetCollisionBox(entity), GetCollisionBox(oEntity));
}

Rectangle CollisionSystem::GetCollisionBox(ECS::Entity* entity)
{
    auto collisionComponent = entity->get<Components::CollisionComponent>();
    auto transformComponent = entity->get<Components::Transform2DComponent>();
    return GetCollisionBox(transformComponent->position, collisionComponent->width, collisionComponent->height);
}

Rectangle CollisionSystem::GetCollisionBox(const Vector2& position, const float& width, const float& height)
{
    return Rectangle{
        position.x - width / 2,
        position.y - height / 2,
        width,
        height
    };
}
