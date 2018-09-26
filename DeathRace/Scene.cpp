#include "Scene.h"
#include "Entities.h"
#include "GameBounds.h"
#include "GameConstants.h"
#include "PlayerIndex.h"

// TODO: remove this once class is all static entity loading/unloading methods
Scene* Scene::currentScene = nullptr;

// TODO: make this a static Load method
Scene::Scene(ECS::World* world, int numPlayers)
    : world(world)
{
    GameBounds::Init(world);

    Vector2 player1Position = Vector2{ (GameConstants::GAME_BOUNDS.width * 0.25f), (GameConstants::GAME_BOUNDS.height * 0.8f) };
    Entities::CreatePlayer(world, PlayerIndex::One, player1Position, WHITE);
    if (numPlayers == 2) {
        Vector2 player2Position = Vector2{ (GameConstants::GAME_BOUNDS.width * 0.75f), (GameConstants::GAME_BOUNDS.height * 0.8f) };
        Entities::CreatePlayer(world, PlayerIndex::Two, player2Position, Color{ 70, 90, 100, 255 });
    }

    float enemyInitialY = (GameConstants::VIRTUAL_HEIGHT * 0.2 + GameConstants::SCOREBOARD_HEIGHT);
    Vector2 enemy1Position = Vector2{
        GameConstants::SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Vector2 enemy2Position = Vector2{
        GameConstants::VIRTUAL_WIDTH - GameConstants::SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Entities::CreateEnemy(world, enemy1Position);
    Entities::CreateEnemy(world, enemy2Position);
}

// TODO: make this a static Unload method
Scene::~Scene()
{
    world->all([&](ECS::Entity* entity) {
        world->destroy(entity);
    });
}

void Scene::Draw()
{
    // TODO: make a GameBoundsSystem that calls this
    GameBounds::Draw();
}

// TODO: remove this once class is all static entity loading/unloading methods
Scene* Scene::GetCurrentScene()
{
    return currentScene;
}

// TODO: remove this once class is all static entity loading/unloading methods
void Scene::SetCurrentScene(Scene* scene)
{
    UnloadCurrentScene();
    currentScene = scene;
}

// TODO: remove this once class is all static entity loading/unloading methods
void Scene::UnloadCurrentScene()
{
    if (currentScene != nullptr) {
        delete currentScene;
        currentScene = nullptr;
    }
}
