#include "GameStateChangedEventSubscriber.h"
#include "raylib.h"

GameState GameStateChangedEventSubscriber::gameState = GameState::Init;

void GameStateChangedEventSubscriber::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    gameState = event.state;
    if (gameState == GameState::MainMenu) {
        SetExitKey(KEY_ESCAPE);
    } else {
        SetExitKey(0);
    }
}

GameState GameStateChangedEventSubscriber::GetGameState()
{
    return gameState;
}
