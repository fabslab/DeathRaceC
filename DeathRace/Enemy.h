#pragma once

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
    void Kill();
    void MakeRandomTurn();
    void UpdateSpriteDirection();

    GraphicUtil::AnimatedTexture *spriteFront, *spriteLeft, *spriteRight, *currentSprite;
    Vector2 initialPosition, position;
};
