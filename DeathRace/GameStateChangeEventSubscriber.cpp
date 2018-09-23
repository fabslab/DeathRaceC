#include "GameStateChangeEventSubscriber.h"
#include "raylib.h"

GameState GameStateChangeEventSubscriber::gameState = GameState::Init;

void GameStateChangeEventSubscriber::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    gameState = event.state;
    if (gameState == GameState::MainMenu) {
        SetExitKey(KEY_ESCAPE);
    } else {
        SetExitKey(0);
    }
}

GameState GameStateChangeEventSubscriber::GetGameState()
{
    return gameState;
}
