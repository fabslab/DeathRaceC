#include "MenuRenderSystem.h"
#include "Scene.h"
#include "raylib.h"

void MenuRenderSystem::configure(ECS::World* world)
{
    gameState = GameState::MainMenu;
    world->subscribe<Events::GameStateChangedEvent>(this);
}

void MenuRenderSystem::unconfigure(ECS::World* world)
{
    world->unsubscribeAll(this);
}

void MenuRenderSystem::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    GameState prevGameState = gameState;
    gameState = event.state;

    if (gameState != prevGameState) {
        if (gameState == GameState::MainMenu) {
            Scene::UnloadCurrentScene();
            SetExitKey(KEY_ESCAPE);
        } else {
            SetExitKey(0);
        }
    }
}

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
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
