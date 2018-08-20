#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
    for (auto collider : colliders) {
        delete collider;
    }
}

BoxCollider* CollisionManager::CreateBoxCollider(float width, float height, CollisionLayer layer, CollisionLayerFilter collisionFilter)
{
    auto collider = new BoxCollider(width, height, layer, collisionFilter);
    colliders[numColliders] = collider;
    return collider;
}
