#pragma once

#include "CollisionLayer.h"
#include "MathUtil.h"
#include "PlayerIndex.h"
#include "raylib.h"

namespace Components {
typedef struct CollisionComponent {
    CollisionComponent(float width, float height, bool isStatic, CollisionLayer layer, CollisionLayer filter)
        : filter(filter)
        , height(height)
        , isStatic(isStatic)
        , layer(layer)
        , width(width)
    {
    }
    CollisionComponent() = default;
    CollisionLayer filter = CollisionLayer::None;
    CollisionLayer layer = CollisionLayer::None;
    float height = 0;
    bool isStatic = true;
    float width = 0;
} CollisionComponent;

typedef struct EnemyMovementComponent {
    EnemyMovementComponent(Vector2 initialPosition, float speed, float timeRangeStart, float timeRangeEnd, float chancePerUpdate)
        : chancePerUpdate(chancePerUpdate)
        , initialPosition(initialPosition)
        , speed(speed)
        , timeRangeEnd(timeRangeEnd)
        , timeRangeStart(timeRangeStart)
    {
    }
    EnemyMovementComponent() = default;
    float chancePerUpdate = 0.f;
    Vector2 direction = DirectionVectors::Down;
    Vector2 initialPosition = Vector2{ 0.f, 0.f };
    float lookDistance = 2.f;
    float speed = 0.f;
    float timeRangeEnd = 0.f;
    float timeRangeStart = 0.f;
    float timeSinceTurn = 0.f;
} EnemyMovementComponent;

typedef struct PlayerMovementComponent {
    PlayerMovementComponent(PlayerIndex playerIndex, float forwardSpeed, float reverseSpeed)
        : forwardSpeed(forwardSpeed)
        , playerIndex(playerIndex)
        , reverseSpeed(reverseSpeed)
    {
    }
    PlayerMovementComponent() = default;
    float crashTime = 1000.f;
    PlayerIndex playerIndex = PlayerIndex::One;
    float forwardSpeed = 0.f;
    float remainingCrashTime = 0.f;
    float reverseSpeed = 0.f;
} PlayerMovementComponent;

typedef struct EnemySafeAreaComponent {
    bool enabled = true;
} EnemySafeAreaComponent;

typedef struct ScoreComponent {
    ScoreComponent(PlayerIndex playerIndex)
        : playerIndex(playerIndex)
    {
    }
    int score = 0;
    PlayerIndex playerIndex = PlayerIndex::One;
} ScoreComponent;

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
    TextureComponent(Texture& texture)
        : texture(texture)
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
