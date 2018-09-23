#include "MenuRenderSystem.h"
#include "Events.h"
#include "GameState.h"
#include "GameStateChangeEventSubscriber.h"
#include "raylib.h"

MenuRenderSystem::MenuRenderSystem()
{
}

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangeEventSubscriber::GetGameState();
    if (gameState == GameState::GameRunning) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            world->emit(Events::GameStateChangeEvent{ GameState::GamePaused });
        }
    } else if (gameState == GameState::GamePaused) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            world->emit(Events::GameStateChangeEvent{ GameState::GameRunning });
        } else {
            pausedMenu.Update();
            pausedMenu.Draw();
        }
    } else if (gameState == GameState::GameOver) {
        gameOverMenu.Update();
        gameOverMenu.Draw();
    } else if (gameState == GameState::MainMenu) {
        // render main menu
    }
}
