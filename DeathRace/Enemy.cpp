#include "Enemy.h"

Enemy::Enemy(Vector2 initialPosition)
{
    this->initialPosition = initialPosition;
    position = initialPosition;
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
}

void Enemy::Update()
{
    currentSprite->Update();
}

void Enemy::Kill()
{
}

void Enemy::MakeRandomTurn()
{
}

void Enemy::UpdateSpriteDirection()
{
}
