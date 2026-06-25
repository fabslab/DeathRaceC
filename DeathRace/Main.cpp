#include "AssetPath.h"
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

#include <iostream>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[])
{
    // Parse command-line arguments
    bool windowed = false;
    bool explicitWidth = false;
    bool explicitHeight = false;
    int windowWidth = GameConstants::VIRTUAL_WIDTH * 2;
    int windowHeight = GameConstants::VIRTUAL_HEIGHT * 2;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--windowed") {
            windowed = true;
        } else if (arg == "--width") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --width requires a value.\n";
                return 1;
            }
            try {
                windowWidth = std::stoi(argv[++i]);
                explicitWidth = true;
            } catch (const std::exception&) {
                std::cerr << "Error: --width requires a numeric value.\n";
                return 1;
            }
            if (windowWidth <= 0) {
                std::cerr << "Error: --width must be positive.\n";
                return 1;
            }
        } else if (arg == "--height") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --height requires a value.\n";
                return 1;
            }
            try {
                windowHeight = std::stoi(argv[++i]);
                explicitHeight = true;
            } catch (const std::exception&) {
                std::cerr << "Error: --height requires a numeric value.\n";
                return 1;
            }
            if (windowHeight <= 0) {
                std::cerr << "Error: --height must be positive.\n";
                return 1;
            }
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Death Race - Command Line Options:\n"
                      << "  --windowed         Start in windowed mode\n"
                      << "  --width <pixels>   Set window width (default: max display)\n"
                      << "  --height <pixels>  Set window height (default: max display)\n"
                      << "  --help, -h         Show this help message\n";
            return 0;
        }
    }

    const float PREFERRED_ASPECT_RATIO = static_cast<float>(GameConstants::VIRTUAL_WIDTH) / GameConstants::VIRTUAL_HEIGHT;
    Image icon = LoadImage(GetAssetPath("Content/icon.png").c_str());

    InitWindow(windowWidth, windowHeight, "Death Race");
    SetWindowMinSize(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    SetWindowIcon(icon);
    // Start windowed — user can toggle fullscreen with Alt+Enter
    InitAudioDevice();
    SetTargetFPS(60);

    // Get monitor size for fullscreen toggle and default window sizing
    const int monitorWidth = GetMonitorWidth(0);
    const int monitorHeight = GetMonitorHeight(0);

    // If no explicit size was given, maximize the window to fill the monitor.
    // The game rendering handles aspect ratio with black bars, so the window
    // can be any size — we just want it as large as possible.
    if (!explicitWidth && !explicitHeight) {
        const int chromeHeight = 64; // title bar + macOS menu bar
        windowWidth = monitorWidth;
        windowHeight = monitorHeight - chromeHeight;

        SetWindowSize(windowWidth, windowHeight);
        int monitorX = 0;
        int monitorY = chromeHeight / 2;
        SetWindowPosition(monitorX, monitorY);
    }

    // Start windowed and use the current window dimensions for rendering
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    Fonts::Load();
    Textures::Load();
    Shaders::Load();
    Shaders::SetDimensions(screenWidth, screenHeight);
    GameAudio::Load();

    auto virtualSizeRectangle = Rectangle { 0, 0, GameConstants::VIRTUAL_WIDTH, -GameConstants::VIRTUAL_HEIGHT };
    Rectangle destinationRectangle = GraphicsUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
    auto virtualRenderTexture = LoadRenderTexture(GameConstants::VIRTUAL_WIDTH, GameConstants::VIRTUAL_HEIGHT);
    SetTextureFilter(virtualRenderTexture.texture, TEXTURE_FILTER_POINT);
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
                SetWindowSize(monitorWidth, monitorHeight);
                SetWindowPosition(0, 0);
            } else {
                SetWindowSize(windowWidth, windowHeight);
                int monitorX = monitorWidth / 2 - windowWidth / 2;
                int monitorY = monitorHeight / 2 - windowHeight / 2;
                SetWindowPosition(monitorX, monitorY);
            }
            // Update render target and aspect ratio to match the new window size
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            UnloadRenderTexture(fullScreenRenderTarget);
            fullScreenRenderTarget = LoadRenderTexture(screenWidth, screenHeight);
            Shaders::SetDimensions(screenWidth, screenHeight);
            destinationRectangle = GraphicsUtil::GetDestinationRectangleForScreen(static_cast<float>(screenWidth), static_cast<float>(screenHeight), PREFERRED_ASPECT_RATIO);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(virtualRenderTexture);
        ClearBackground(BLACK);

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
    delete gameStateSubscriber; // gameStateSubscriber is not owned by the world
    // Note: ECS systems (AnimationSystem, PlayerMovementSystem, etc.) are owned by the world
    // and are deleted automatically by destroyWorld().
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
