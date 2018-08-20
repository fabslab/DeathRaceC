#pragma once

#include "AggregatedPlayerInput.h"
#include "BoxCollider.h"
#include "PlayerInput.h"
#include "raylib.h"
#include <vector>

class Player {
public:
    Player(Vector2 initialPosition, int playerIndex, std::vector<PlayerInput*> supportedInputs, Color color);
    ~Player();
    void Draw();
    void Update();
    void Reset();

private:
    Texture2D texture;
    Vector2 initialPosition, position;
    float rotation, snappedRotation;
    Color color;
    AggregatedPlayerInput* input;
    BoxCollider* collider;

    // Max number of pixels to move in one update
    float maxForwardSpeed = 2;
    float maxReverseSpeed = 1;

    // Maximum turn value in one update in radians
    float turnAmount = PI / 48;
    float rotationSnapAngle = PI / 8;

    // Initial direction for car to be facing (up or -Y direction)
    Vector3 initialDirection = { 0, -1, 0 };
};
