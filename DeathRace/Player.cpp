#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include "MathUtil.h"
#include "Constants.h"

Player::Player(Vector2 initialPosition, int playerIndex, std::vector<PlayerInput*> supportedInputs, Color color)
{
	texture = LoadTexture("Content/car16bit02.png");
	sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
	origin = { static_cast<float>(texture.width)/2, static_cast<float>(texture.height)/2 };
	input = new AggregatedPlayerInput(supportedInputs);
	this->initialPosition = initialPosition;
	this->color = color;
	Reset();
}

Player::~Player()
{
	UnloadTexture(texture);
	delete input;
}

void Player::Draw()
{
	Rectangle destRec = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
	DrawTexturePro(texture, sourceRec, destRec, origin, snappedRotation * RAD2DEG, color);
}

void Player::Update()
{
	float throttle = input->GetThrottleValue();
	float maxSpeed = throttle > 0 ? maxForwardSpeed : maxReverseSpeed;
	float speed = maxSpeed * throttle;
	float turnAngle = input->GetDirection() * turnAmount;
	
	// Reset rotation back to snapped value if player stops turning
	if (turnAngle == 0) 
	{ 
		rotation = snappedRotation; 
	}
	else
	{
		rotation += turnAngle;

		// Prevent value from becoming too large by resetting once full circle reached
		if (rotation >= (PI * 2) || rotation <= -(PI * 2))
		{
			rotation = snappedRotation = 0;
		}
		else
		{
			snappedRotation = MathUtil::Snap(rotation, rotationSnapAngle);
		}
	}

	if (speed == 0 && turnAngle == 0)
	{
		return;
	}

	Matrix rotationMatrix = MatrixRotateZ(-snappedRotation);
	Vector3 movementDirection = Vector3Transform(initialDirection, rotationMatrix);
	Vector3 movement = Vector3Multiply(movementDirection, speed);

	position = MathUtil::WrapPosition(Vector2Add(position, { movement.x, movement.y }), GAME_BOUNDS);
}

void Player::Reset()
{
	position = initialPosition;
	rotation = snappedRotation = 0;
}
