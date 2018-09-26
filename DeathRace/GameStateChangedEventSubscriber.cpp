#include "GameStateChangedEventSubscriber.h"
#include "raylib.h"

GameState GameStateChangedEventSubscriber::gameState = GameState::MainMenu;

void GameStateChangedEventSubscriber::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    gameState = event.state;
}

GameState GameStateChangedEventSubscriber::GetGameState()
{
    return gameState;
}
