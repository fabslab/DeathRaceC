#pragma once

#include "ECS.h"
#include "GraphicsUtil.h"
#include "raylib.h"

class Enemy {
public:
    Enemy(ECS::Entity* entity, Vector2 initialPosition);
};
