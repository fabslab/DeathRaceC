#include "PlayerMovementSystem.h"
#include "Components.h"
#include "Constants.h"
#include "GameStateChangeEventSubscriber.h"
#include "MathUtil.h"
#include "raymath.h"
#include <algorithm>

PlayerMovementSystem::PlayerMovementSystem()
{
    keyboardInputLeft = new KeyboardPlayerInput(Input::PLAYER_LEFT);
    keyboardInputRight = new KeyboardPlayerInput(Input::PLAYER_RIGHT);
}

PlayerMovementSystem::~PlayerMovementSystem()
{
    delete keyboardInputLeft;
    delete keyboardInputRight;
}

void PlayerMovementSystem::tick(ECS::World* world, float deltaTime)
{
    if (GameStateChangeEventSubscriber::GetGameState() != GameState::GameRunning) {
        return;
    }

    world->each<Components::PlayerMovementComponent, Components::SnappedRotationComponent, Components::Transform2DComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::PlayerMovementComponent> movementComponent,
            ECS::ComponentHandle<Components::SnappedRotationComponent> snappedRotationComponent,
            ECS::ComponentHandle<Components::Transform2DComponent> transformComponent) {
            if (numPlayers == 1) {
                inputAggregator.SetInputs({ keyboardInputLeft, keyboardInputRight });
            } else if (numPlayers == 2) {
                if (movementComponent->playerIndex == PlayerIndex::One) {
                    inputAggregator.SetInputs({ keyboardInputLeft });
                } else if (movementComponent->playerIndex == PlayerIndex::Two) {
                    inputAggregator.SetInputs({ keyboardInputRight });
                }
            }

            float throttle = inputAggregator.GetThrottleValue();
            float turnDirection = inputAggregator.GetDirection();

            movementComponent->remainingCrashTime = std::max(movementComponent->remainingCrashTime - deltaTime, 0.f);
            if (throttle < 0.f) {
                movementComponent->remainingCrashTime = 0.f;
            }

            if (movementComponent->remainingCrashTime <= 0.f) {
                float rotation = transformComponent->rotation;
                if (turnDirection == 0.f) {
                    // Reset rotation back to snapped value if player stops turning
                    rotation = MathUtil::Snap(rotation, snappedRotationComponent->snapAngle);
                } else {
                    rotation += (turnDirection * snappedRotationComponent->maxTurnPerUpdate);
                    // Prevent value from becoming too large by resetting once full circle reached
                    float pi2 = PI * 2;
                    if (rotation > pi2) {
                        rotation -= pi2;
                    } else if (rotation < -pi2) {
                        rotation += pi2;
                    }
                }
                transformComponent->rotation = rotation;

                if (throttle != 0.f) {
                    float speed = throttle > 0.f
                        ? throttle * movementComponent->forwardSpeed
                        : throttle * movementComponent->reverseSpeed;
                    float snappedRotation = MathUtil::Snap(rotation, snappedRotationComponent->snapAngle);
                    Matrix rotationMatrix = MatrixRotateZ(-snappedRotation);
                    Vector3 movementDirection = Vector3Transform(MathUtil::Vector2To3(DirectionVectors::Down), rotationMatrix);
                    Vector3 movement = Vector3Multiply(movementDirection, speed);
                    transformComponent->position = MathUtil::WrapPosition(
                        Vector2Add(transformComponent->position, MathUtil::Vector3To2(movement)),
                        GameConstants::GAME_BOUNDS);
                }
            }

            // Store result of this tick to enable replays
            movementCommandBuffer[static_cast<int>(movementComponent->playerIndex)].push_back(
                PlayerMovementCommand{ transformComponent->position, transformComponent->rotation });
        });
}

void PlayerMovementSystem::SetCommandBuffers(std::array<std::vector<PlayerMovementCommand>, 2>& buffer)
{
    movementCommandBuffer = buffer;
}

std::array<std::vector<PlayerMovementCommand>, 2> PlayerMovementSystem::GetCommandBuffers()
{
    return movementCommandBuffer;
}

void PlayerMovementSystem::ClearCommandBuffers()
{
    for (auto buffer : movementCommandBuffer) {
        buffer.clear();
    }
}

void PlayerMovementSystem::SetNumPlayers(int numPlayers)
{
    this->numPlayers = numPlayers;
}