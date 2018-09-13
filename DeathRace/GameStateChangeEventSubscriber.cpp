#include "GameStateChangeEventSubscriber.h"

GameState GameStateChangeEventSubscriber::gameState = GameState::Init;

void GameStateChangeEventSubscriber::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    gameState = event.state;
}

GameState GameStateChangeEventSubscriber::GetGameState()
{
    return gameState;
}
