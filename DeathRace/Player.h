#pragma once

#include "ECS.h"
#include "raylib.h"

class Player {
public:
    Player(ECS::Entity* entity, int playerIndex, Vector2 position, Color color);

private:
    // Max number of pixels to move in one update
    //float maxForwardSpeed = 2;
    //float maxReverseSpeed = 1;

    // Maximum turn value in one update in radians
    //float turnAmount = PI / 48;

    // Initial direction for car to be facing (up or -Y direction)
    //Vector3 initialDirection = { 0, -1, 0 };
};
