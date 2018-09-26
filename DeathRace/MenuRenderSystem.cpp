#include "MenuRenderSystem.h"
#include "Events.h"
#include "GameState.h"
#include "GameStateChangedEventSubscriber.h"
#include "raylib.h"

MenuRenderSystem::MenuRenderSystem()
{
}

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangedEventSubscriber::GetGameState();
    if (gameState == GameState::GameRunning) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            world->emit(Events::GameStateChangedEvent{ GameState::GamePaused });
        }
    } else if (gameState == GameState::GamePaused) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            world->emit(Events::GameStateChangedEvent{ GameState::GameRunning });
        } else {
            pausedMenu.Update(world);
            pausedMenu.Draw();
        }
    } else if (gameState == GameState::GameOver) {
        gameOverMenu.Update(world);
        gameOverMenu.Draw();
    } else if (gameState == GameState::MainMenu) {
        mainMenu.Update(world);
        mainMenu.Draw();
    }
}
