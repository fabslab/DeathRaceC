#include "MenuRenderSystem.h"
#include "KeyboardInputMap.h"
#include "PlayerIndex.h"
#include "Scene.h"
#include "raylib.h"

void MenuRenderSystem::configure(ECS::World* world)
{
    gameState = GameState::MainMenu;
    world->subscribe<Events::GameStateChangedEvent>(this);
    keyboardInput = new KeyboardPlayerInput(Input::UI_NAVIGATION);
    controllerInputOne = new ControllerPlayerInput(PlayerIndex::One);
    controllerInputTwo = new ControllerPlayerInput(PlayerIndex::Two);
    inputAggregator.SetInputs({ keyboardInput, controllerInputOne, controllerInputTwo });
}

void MenuRenderSystem::unconfigure(ECS::World* world)
{
    world->unsubscribeAll(this);
    delete keyboardInput;
    delete controllerInputOne;
    delete controllerInputTwo;
}

void MenuRenderSystem::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    GameState prevGameState = gameState;
    gameState = event.state;

    if (gameState != prevGameState) {
        if (gameState == GameState::MainMenu) {
            Scene::Unload(world);
            SetExitKey(KEY_ESCAPE);
        } else {
            SetExitKey(0);
        }
        if (gameState == GameState::GameOver) {
            gameOverMenu.SetPlayerScores(event.scores);
        }
    }
}

void MenuRenderSystem::tick(ECS::World* world, float deltaTime)
{
    if (gameState == GameState::GameRunning) {
        if (inputAggregator.WasCommandEntered(Input::InputCommand::Pause)) {
            world->emit(Events::GameStateChangedEvent { GameState::GamePaused });
        }
    } else if (gameState == GameState::GamePaused) {
        if (inputAggregator.WasCommandEntered(Input::InputCommand::Pause)
            || inputAggregator.WasCommandEntered(Input::InputCommand::Back)) {
            world->emit(Events::GameStateChangedEvent { GameState::GameRunning });
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
