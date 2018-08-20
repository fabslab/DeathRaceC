#pragma once

#include "BoxCollider.h"
#include <array>

class CollisionManager {
public:
    ~CollisionManager();
    BoxCollider* CreateBoxCollider(float width, float height, CollisionLayer layer, CollisionLayerFilter collisionFilter);

private:
    std::array<BoxCollider*, 10> colliders;
    int numColliders = 0;
};
