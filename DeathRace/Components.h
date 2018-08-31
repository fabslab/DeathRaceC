#pragma once

#include "CollisionLayer.h"
#include "MathUtil.h"
#include "raylib.h"

namespace Components {
typedef struct CollisionComponent {
    CollisionComponent(float width, float height, CollisionLayer layer, CollisionLayer filter)
        : filter(filter)
        , height(height)
        , layer(layer)
        , width(width)
    {
    }
    CollisionComponent() = default;
    CollisionLayer filter = CollisionLayer::None;
    CollisionLayer layer = CollisionLayer::None;
    float height = 0;
    float width = 0;
} CollisionComponent;

typedef struct EnemyMovementComponent {
    EnemyMovementComponent(float speed, float timeRangeStart, float timeRangeEnd, float chancePerUpdate)
        : chancePerUpdate(chancePerUpdate)
        , speed(speed)
        , timeRangeEnd(timeRangeEnd)
        , timeRangeStart(timeRangeStart)
    {
    }
    EnemyMovementComponent() = default;
    float chancePerUpdate = 0.f;
    Vector2 direction = DirectionVectors::Down;
    float lookDistance = 2.f;
    float speed = 0.f;
    float timeRangeEnd = 0.f;
    float timeRangeStart = 0.f;
    float timeSinceTurn = 0.f;
} EnemyMovementComponent;

typedef struct PlayerMovementComponent {
    PlayerMovementComponent(int playerIndex, float forwardSpeed, float reverseSpeed)
        : forwardSpeed(forwardSpeed)
        , playerIndex(playerIndex)
        , reverseSpeed(reverseSpeed)
    {
    }
    PlayerMovementComponent() = default;
    int playerIndex = 0;
    float forwardSpeed = 0.f;
    float reverseSpeed = 0.f;
} PlayerMovementComponent;

typedef struct SnappedRotationComponent {
    float snapAngle = PI / 8;
    float maxTurnPerUpdate = PI / 48;
} SnappedRotationComponent;

typedef struct TextureAnimationComponent {
    TextureAnimationComponent(int frameCount, float frameDurationMs)
        : frameCount(frameCount)
        , frameDurationMs(frameDurationMs)
    {
    }
    TextureAnimationComponent() = default;
    int currentFrameIndex = 0;
    int frameCount = 0;
    float frameDurationMs = 0.f;
    float remainingFrameTime = 0.f;
} TextureAnimationComponent;

typedef struct TextureComponent {
    TextureComponent(Texture& texture, Color tint, Rectangle sourceRect)
        : sourceRect(sourceRect)
        , texture(texture)
        , tint(tint)
    {
    }
    TextureComponent(Texture& texture, Color tint)
        : texture(texture)
        , tint(tint)
    {
        sourceRect = Rectangle{ 0.f, 0.f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    }
    TextureComponent()
        = default;
    Rectangle sourceRect;
    Texture texture;
    Color tint = WHITE;
} TextureComponent;

typedef struct Transform2DComponent {
    Transform2DComponent(Vector2 position, float rotation)
        : position(position)
        , rotation(rotation)
    {
    }
    Transform2DComponent(Vector2 position)
        : position(position)
    {
    }
    Transform2DComponent() = default;
    Vector2 position = { 0.f, 0.f };
    float rotation = 0.f;
} Transform2DComponent;
}
