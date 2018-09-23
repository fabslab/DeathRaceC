#include "MenuRenderSystem.h"
#include "GameState.h"
#include "GameStateChangeEventSubscriber.h"

MenuRenderSystem::MenuRenderSystem()
{
}

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangeEventSubscriber::GetGameState();
    if (gameState == GameState::GamePaused) {
        // render paused menu
    } else if (gameState == GameState::GameOver) {
        gameOverMenu.Update();
        gameOverMenu.Draw();
    } else if (gameState == GameState::MainMenu) {
        // render main menu
    }
}
