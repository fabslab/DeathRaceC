#pragma once

#include <cstdint>

using CollisionLayerFilter = uint_fast32_t;

const enum class CollisionLayer : CollisionLayerFilter {
    None = 0,
    Player = 1 << 0,
    Enemy = 1 << 1,
    RoadBounds = 1 << 2,
    GameBounds = 1 << 3,
    All = ~None
};
