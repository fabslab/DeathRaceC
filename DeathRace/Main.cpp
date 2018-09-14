#include "raylib.h"

#include "AnimationSystem.h"
#include "CollisionEventSubscriber.h"
#include "CollisionSystem.h"
#include "Constants.h"
#include "EnemyMovementSystem.h"
#include "Events.h"
#include "Fonts.h"
#include "GameState.h"
#include "GameStateChangeEventSubscriber.h"
#include "GraphicsUtil.h"
#include "PlayerMovementSystem.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "ScoreRenderSystem.h"

int main(int argc, char* argv[])
{
    const float PREFERRED_ASPECT_RATIO = static_cast<float>(GameConstants::VIRTUAL_WIDTH) / GameConstants::VIRTUAL_HEIGHT;

    int screenWidth = 1920 / 3 * 2;
    int screenHeight = 1080 / 3 * 2;

    InitWindow(screenWidth, screenHeight, "Death Race");
    SetWindowMinSize(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    //ToggleFullscreen();

    SetTargetFPS(60);

    auto virtualSizeRectangle = Rectangle{ 0, 0, GameConstants::VIRTUAL_WIDTH, -GameConstants::VIRTUAL_HEIGHT };
    auto destinationRectangle = GraphicsUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
    auto virtualRenderTexture = LoadRenderTexture(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    SetTextureFilter(virtualRenderTexture.texture, FILTER_POINT);
    auto screenOrigin = Vector2{ 0, 0 };

    Fonts::Load();

    int numPlayers = 2;
    auto world = ECS::World::createWorld();

    auto gameStateSubscriber = new GameStateChangeEventSubscriber();
    world->subscribe<Events::GameStateChangedEvent>(gameStateSubscriber);
    world->subscribe<Events::CollisionEvent>(new CollisionEventSubscriber());

    world->registerSystem(new AnimationSystem());
    auto playerMovement = new PlayerMovementSystem();
    playerMovement->SetNumPlayers(numPlayers);
    world->registerSystem(playerMovement);
    world->registerSystem(new EnemyMovementSystem());
    world->registerSystem(new CollisionSystem());
    world->registerSystem(new RenderSystem());
    world->registerSystem(new ScoreRenderSystem(GameConstants::GAME_TIME));

    auto scene = Scene(world, numPlayers);

    world->emit(Events::GameStateChangedEvent{ GameState::GameRunning });

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(virtualRenderTexture);

        world->tick(GetFrameTime() * 1000);
        scene.Draw();

        EndTextureMode();

        DrawTexturePro(
            virtualRenderTexture.texture,
            virtualSizeRectangle,
            destinationRectangle,
            screenOrigin,
            0,
            WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    world->destroyWorld();
    Fonts::Unload();
    UnloadRenderTexture(virtualRenderTexture);
    CloseWindow();

    return 0;
}
