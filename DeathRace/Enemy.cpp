#include "Enemy.h"
#include "MathUtil.h"
#include <stdio.h>

Enemy::Enemy(Vector2 initialPosition)
    : initialPosition(initialPosition)
{
    position = initialPosition;
    initialDirection = DirectionVectors::Down;
    direction = initialDirection;
    spriteFront = new GraphicUtil::AnimatedTexture("Content/gremlin-front.png", 2, 60);
    spriteLeft = new GraphicUtil::AnimatedTexture("Content/gremlin-left.png", 2, 60);
    spriteRight = new GraphicUtil::AnimatedTexture("Content/gremlin-right.png", 2, 60);
    currentSprite = spriteFront;
}

Enemy::~Enemy()
{
    delete spriteFront;
    delete spriteLeft;
    delete spriteRight;
}

void Enemy::Draw()
{
    currentSprite->Draw(position);
}

void Enemy::Reset()
{
    position = initialPosition;
    direction = initialDirection;
    timeSinceTurnMs = 0.0f;
}

void Enemy::Update()
{
    float timeSinceLastFrameMs = GetFrameTime() * 1000;
    timeSinceTurnMs += timeSinceLastFrameMs;

    if (ShouldMakeTurn()) {
        MakeRandomTurn();
    } else {
        currentSprite->Update(timeSinceLastFrameMs);
    }

    position = Vector2Add(position, Vector2Scale(direction, speed));
}

void Enemy::Die()
{
    Reset();
}

bool Enemy::ShouldMakeTurn()
{
    // 5% chance to turn each update during set time range
    // assumes 60hz update rate
    // if end of range reached, force a turn
    bool shouldTurn = false;
    if (timeSinceTurnMs >= timeRangeForRandomTurnMs[1]) {
        shouldTurn = true;
    } else if (timeSinceTurnMs >= timeRangeForRandomTurnMs[0]) {
        shouldTurn = GetRandomValue(0, 19) == 0;
    }
    return shouldTurn;
}

void Enemy::MakeRandomTurn()
{
    // 50/50 chance to turn left/right
    Vector3 turnDirection = Vector3CrossProduct({ direction.x, direction.y, 0 }, { 0, 0, 1 });
    if (GetRandomValue(0, 1) == 0) {
        turnDirection = { -turnDirection.x, -turnDirection.y, 0 };
    }
    direction = { turnDirection.x, turnDirection.y };
    UpdateSpriteDirection();
    timeSinceTurnMs = 0;
}

void Enemy::UpdateSpriteDirection()
{
    if (direction == DirectionVectors::Left) {
        currentSprite = spriteLeft;
    } else if (direction == DirectionVectors::Right) {
        currentSprite = spriteRight;
    } else {
        currentSprite = spriteFront;
    }
    currentSprite->Reset();
}
