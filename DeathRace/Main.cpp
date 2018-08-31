#include "raylib.h"

#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "Constants.h"
#include "EnemyMovementSystem.h"
#include "GraphicUtil.h"
#include "PlayerMovementSystem.h"
#include "RenderSystem.h"
#include "Scene.h"

int main(int argc, char* argv[])
{
    const float PREFERRED_ASPECT_RATIO = static_cast<float>(VIRTUAL_WIDTH) / VIRTUAL_HEIGHT;

    int screenWidth = 1920;
    int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Death Race");
    SetWindowMinSize(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    ToggleFullscreen();

    SetTargetFPS(60);

    auto virtualSizeRectangle = Rectangle{ 0, 0, VIRTUAL_WIDTH, -VIRTUAL_HEIGHT };
    auto destinationRectangle = GraphicUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
    auto virtualRenderTexture = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(virtualRenderTexture.texture, FILTER_POINT);
    auto screenOrigin = Vector2{ 0, 0 };

    int numPlayers = 2;
    auto world = ECS::World::createWorld();
    auto scene = Scene(world, numPlayers);
    world->registerSystem(new AnimationSystem());
    auto playerMovement = new PlayerMovementSystem();
    playerMovement->SetNumPlayers(numPlayers);
    world->registerSystem(playerMovement);
    world->registerSystem(new EnemyMovementSystem());
    world->registerSystem(new CollisionSystem());
    world->registerSystem(new RenderSystem());

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(virtualRenderTexture);

        world->tick(GetFrameTime() * 1000);
        scene.Draw();
        DrawFPS(2, 2);

        EndTextureMode();

        DrawTexturePro(
            virtualRenderTexture.texture,
            virtualSizeRectangle,
            destinationRectangle,
            screenOrigin,
            0,
            WHITE);

        EndDrawing();
    }

    world->destroyWorld();

    UnloadRenderTexture(virtualRenderTexture);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
