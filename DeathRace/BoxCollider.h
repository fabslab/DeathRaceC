#pragma once

#include "CollisionLayer.h"
#include "raylib.h"

class BoxCollider {
public:
    BoxCollider(float width, float height, CollisionLayer layer, CollisionLayerFilter layerFilter);
    bool Collides(const BoxCollider& other);
    void Draw();
    void SetPosition(Vector2 position);
    CollisionLayer layer;
    CollisionLayerFilter collisionFilter;

private:
    float width, height;
    Vector2 position;
    Rectangle bounds;
};
