#include "PlayerMovementSystem.h"
#include "Components.h"
#include "ControllerInputMap.h"
#include "GameAudio.h"
#include "GameConstants.h"
#include "GameStateChangedEventSubscriber.h"
#include "MathUtil.h"
#include "raymath.h"
#include <algorithm>

void PlayerMovementSystem::configure(ECS::World* world)
{
    world->subscribe<Events::NumberOfPlayersChanged>(this);
    keyboardInputLeft = new KeyboardPlayerInput(Input::PLAYER_LEFT);
    keyboardInputRight = new KeyboardPlayerInput(Input::PLAYER_RIGHT);
    controllerInputOne = new ControllerPlayerInput(Input::PS4_GAMEPAD, PlayerIndex::One);
    controllerInputTwo = new ControllerPlayerInput(Input::PS4_GAMEPAD, PlayerIndex::Two);
}

void PlayerMovementSystem::unconfigure(ECS::World* world)
{
    world->unsubscribeAll(this);
    delete keyboardInputLeft;
    delete keyboardInputRight;
    delete controllerInputOne;
    delete controllerInputTwo;
    for (auto sound : playerEngineSounds) {
        if (sound != 0) {
            StopMusicStream(sound);
            UnloadMusicStream(sound);
        }
    }
}

void PlayerMovementSystem::receive(ECS::World* world, const Events::NumberOfPlayersChanged& event)
{
    numPlayers = event.numberOfPlayers;
}

void PlayerMovementSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangedEventSubscriber::GetGameState();
    if (gameState != GameState::GameRunning) {
        return;
    }

    // Play a single idle sound even if two players, two sounds together sounds too overwhelming for an idle sound.
    UpdateEngineIdleSound();

    world->each<Components::PlayerMovementComponent, Components::SnappedRotationComponent, Components::Transform2DComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::PlayerMovementComponent> movementComponent,
            ECS::ComponentHandle<Components::SnappedRotationComponent> snappedRotationComponent,
            ECS::ComponentHandle<Components::Transform2DComponent> transformComponent) {
            if (numPlayers == 1) {
                inputAggregator.SetInputs({ keyboardInputLeft, keyboardInputRight, controllerInputOne, controllerInputTwo });
            } else if (numPlayers == 2) {
                if (movementComponent->playerIndex == PlayerIndex::One) {
                    inputAggregator.SetInputs({ keyboardInputLeft, controllerInputOne });
                } else if (movementComponent->playerIndex == PlayerIndex::Two) {
                    inputAggregator.SetInputs({ keyboardInputRight, controllerInputTwo });
                }
            }

            float throttle = inputAggregator.GetThrottleValue();
            float turnDirection = inputAggregator.GetDirection();

            UpdateEngineRunningSound(movementComponent->playerIndex, throttle);

            movementComponent->remainingCrashTime = std::max(movementComponent->remainingCrashTime - deltaTime, 0.f);
            if (throttle < 0.f) {
                turnDirection = -turnDirection;
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

void PlayerMovementSystem::UpdateEngineIdleSound()
{
    if (engineIdleSound == nullptr) {
        engineIdleSound = LoadMusicStream("Content/Audio/engine-idle-loop.ogg");
        PlayMusicStream(engineIdleSound);
    }
    UpdateMusicStream(engineIdleSound);
}

void PlayerMovementSystem::UpdateEngineRunningSound(PlayerIndex playerIndex, float throttle)
{
    int engineSoundIndex = static_cast<int>(playerIndex);
    Music engineSound = playerEngineSounds[engineSoundIndex];

    if (engineSound == nullptr) {
        engineSound = playerEngineSounds[engineSoundIndex] = LoadMusicStream("Content/Audio/engine-running-loop.ogg");
    }

    UpdateMusicStream(engineSound);

    if (throttle != 0.f) {
        if (!IsMusicPlaying(engineSound)) {
            PlayMusicStream(engineSound);
        }
        float volume = 1.f;
        playerEngineVolumes[engineSoundIndex] = volume;
        SetMusicVolume(engineSound, volume);
    } else {
        if (playerEngineVolumes[engineSoundIndex] < 0.1f) {
            StopMusicStream(engineSound);
        } else {
            playerEngineVolumes[engineSoundIndex] -= 0.1f;
            SetMusicVolume(engineSound, playerEngineVolumes[engineSoundIndex]);
        }
    }
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
