#pragma once

#include <cstdint>

using CollisionLayerFilter = uint_fast32_t;

const enum class CollisionLayer {
    None = 0,
    Player = 1 << 0,
    Enemy = 1 << 1,
    RoadBounds = 1 << 2,
    GameBounds = 1 << 3
};

inline CollisionLayer operator|(CollisionLayer a, CollisionLayer b)
{
    return static_cast<CollisionLayer>(static_cast<uint_fast32_t>(a) | static_cast<uint_fast32_t>(b));
}

inline CollisionLayer operator&(CollisionLayer a, CollisionLayer b)
{
    return static_cast<CollisionLayer>(static_cast<uint_fast32_t>(a) & static_cast<uint_fast32_t>(b));
}

inline CollisionLayer operator~(CollisionLayer a)
{
    return static_cast<CollisionLayer>(~static_cast<uint_fast32_t>(a));
}
