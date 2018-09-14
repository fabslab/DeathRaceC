#include "MenuRenderSystem.h"
#include "GameState.h"
#include "GameStateChangeEventSubscriber.h"

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangeEventSubscriber::GetGameState();
    if (gameState == GameState::GamePaused) {
        // render paused menu
    } else if (gameState == GameState::GameOver) {
        // render game over menu
    } else if (gameState == GameState::MainMenu) {
        // render main menu
    }
}
