#pragma once

#include "raylib.h"
#include "PlayerInput.h"
#include "AggregatedPlayerInput.h"
#include <vector>

class Player
{
public:
	Player(Vector2 initialPosition, int playerIndex, std::vector<PlayerInput*> supportedInputs, Color color);
	~Player();
	void Draw();
	void Update();
	void Reset();
private:
	Texture2D texture;
	Vector2 initialPosition, position, origin;
	float rotation, snappedRotation;
	Rectangle sourceRec;
	Color color;
	AggregatedPlayerInput *input;
	
	// Max number of pixels to move in one update
	const float maxForwardSpeed = 2;
	const float maxReverseSpeed = 1;

	// Maximum turn value in one update in radians
	const float turnAmount = PI / 48;
	const float rotationSnapAngle = PI / 8;

	// Initial direction for car to be facing (up or -Y direction)
	const Vector3 initialDirection = { 0, -1, 0 };
};
