#include "BoxCollider.h"

BoxCollider::BoxCollider(float width, float height, CollisionLayer layer, CollisionLayerFilter collisionFilter)
    : width(width)
    , height(height)
    , layer(layer)
    , collisionFilter(collisionFilter)
{
}

void BoxCollider::Draw()
{
    DrawRectangleRec(this->bounds, RED);
}

bool BoxCollider::Collides(const BoxCollider& other)
{
    return CheckCollisionRecs(this->bounds, other.bounds);
}

void BoxCollider::SetPosition(Vector2 position)
{
    this->position = position;
    bounds = { position.x, position.y, width, height };
}
