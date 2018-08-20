#pragma once

#include "BoxCollider.h"
#include "GraphicUtil.h"
#include "raylib.h"

class Enemy {
public:
    Enemy(Vector2 initialPosition);
    ~Enemy();
    void Draw();
    void Reset();
    void Update();

private:
    void Die();
    void MakeRandomTurn();
    bool ShouldMakeTurn();
    void UpdateSpriteDirection();

    GraphicUtil::AnimatedTexture *spriteFront, *spriteLeft, *spriteRight, *currentSprite;
    BoxCollider* collider;
    Vector2 initialPosition, position, initialDirection, direction;
    float timeSinceTurnMs;
    const float timeRangeForRandomTurnMs[2] = { 350.0f, 1800.0f };
    const float speed = 1.5f;
};
