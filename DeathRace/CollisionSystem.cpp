#include "CollisionSystem.h"
#include "Components.h"
#include "Events.h"
#include <algorithm>

void CollisionSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<Components::CollisionComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::CollisionComponent> collisionComponent) {
            if (!collisionComponent->isStatic) {
                auto previousCollisions = collisionComponent->currentCollisions;
                collisionComponent->currentCollisions.clear();
                world->each<Components::CollisionComponent>(
                    [&](ECS::Entity* oEntity,
                        ECS::ComponentHandle<Components::CollisionComponent> oCollisionComponent) {
                        if (PassesCollisionFilter(entity, oEntity) && AreColliding(entity, oEntity)) {
                            collisionComponent->currentCollisions.push_back(oEntity);
                            auto it = std::find(previousCollisions.begin(), previousCollisions.end(), oEntity);
                            if (it == previousCollisions.end()) {
                                world->emit(Events::CollisionEnteredEvent { entity, oEntity });
                            }
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
    return Rectangle {
        position.x - width / 2,
        position.y - height / 2,
        width,
        height
    };
}
