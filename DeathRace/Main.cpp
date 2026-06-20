#include "raylib.h"

#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "EnemyMovementSystem.h"
#include "Events.h"
#include "Fonts.h"
#include "GameAudio.h"
#include "GameConstants.h"
#include "GameState.h"
#include "GameStateChangedEventSubscriber.h"
#include "GraphicsUtil.h"
#include "MenuRenderSystem.h"
#include "PlayerMovementSystem.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "ScoreRenderSystem.h"
#include "Shaders.h"
#include "Textures.h"

int main(int argc, char* argv[])
{
    const float PREFERRED_ASPECT_RATIO = static_cast<float>(GameConstants::VIRTUAL_WIDTH) / GameConstants::VIRTUAL_HEIGHT;
    Image icon = LoadImage("Content/icon.png");

    const int WINDOW_SCALE = 2;
    const int windowWidth = GameConstants::VIRTUAL_WIDTH * WINDOW_SCALE;
    const int windowHeight = GameConstants::VIRTUAL_HEIGHT * WINDOW_SCALE;

    InitWindow(windowWidth, windowHeight, "Death Race");
    SetWindowMinSize(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    SetWindowIcon(icon);
    // Start windowed — user can toggle fullscreen with Alt+Enter
    InitAudioDevice();
    SetTargetFPS(60);

    // Get monitor size for fullscreen toggle
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    Fonts::Load();
    Textures::Load();
    Shaders::Load();
    Shaders::SetDimensions(screenWidth, screenHeight);
    GameAudio::Load();

    auto virtualSizeRectangle = Rectangle { 0, 0, GameConstants::VIRTUAL_WIDTH, -GameConstants::VIRTUAL_HEIGHT };
    Rectangle destinationRectangle = GraphicsUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
    auto virtualRenderTexture = LoadRenderTexture(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    SetTextureFilter(virtualRenderTexture.texture, FILTER_POINT);
    auto fullScreenRenderTarget = LoadRenderTexture(screenWidth, screenHeight);
    auto screenOrigin = Vector2 { 0, 0 };

    auto world = ECS::World::createWorld();
    auto gameStateSubscriber = new GameStateChangedEventSubscriber();
    world->subscribe<Events::GameStateChangedEvent>(gameStateSubscriber);
    world->registerSystem(new AnimationSystem());
    world->registerSystem(new PlayerMovementSystem());
    world->registerSystem(new EnemyMovementSystem());
    world->registerSystem(new CollisionSystem());
    world->registerSystem(new RenderSystem());
    world->registerSystem(new ScoreRenderSystem());
    world->registerSystem(new MenuRenderSystem());

    GameState gameState = GameStateChangedEventSubscriber::GetGameState();

    while (!WindowShouldClose() && gameState != GameState::Exit) {
        // Toggle fullscreen on Alt+Enter
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
            ToggleFullscreen();
            if (IsWindowFullscreen()) {
                SetWindowSize(screenWidth, screenHeight);
                SetWindowPosition(0, 0);
            } else {
                SetWindowSize(windowWidth, windowHeight);
                int monitorX = GetMonitorWidth(0) / 2 - windowWidth / 2;
                int monitorY = GetMonitorHeight(0) / 2 - windowHeight / 2;
                SetWindowPosition(monitorX, monitorY);
            }
            // Recalculate destination rectangle for aspect ratio
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            destinationRectangle = GraphicsUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(virtualRenderTexture);

        world->tick(GetFrameTime() * 1000);

        gameState = GameStateChangedEventSubscriber::GetGameState();

        EndTextureMode();

        BeginTextureMode(fullScreenRenderTarget);
        BeginShaderMode(Shaders::scanLines);
        DrawTexturePro(
            virtualRenderTexture.texture,
            virtualSizeRectangle,
            destinationRectangle,
            screenOrigin,
            0,
            WHITE);
        EndTextureMode();
        EndShaderMode();

        BeginShaderMode(Shaders::bloom);
        DrawTextureRec(
            fullScreenRenderTarget.texture,
            Rectangle {
                0.f,
                0.f,
                static_cast<float>(fullScreenRenderTarget.texture.width),
                static_cast<float>(-fullScreenRenderTarget.texture.height) },
            screenOrigin,
            WHITE);
        EndShaderMode();

        EndDrawing();
    }

    UnloadImage(icon);
    world->destroyWorld();
    GameAudio::Unload();
    Shaders::Unload();
    Textures::Unload();
    Fonts::Unload();
    UnloadRenderTexture(virtualRenderTexture);
    UnloadRenderTexture(fullScreenRenderTarget);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
