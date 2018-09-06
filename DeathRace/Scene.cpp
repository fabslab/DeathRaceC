#include "Scene.h"
#include "Constants.h"
#include "Entities.h"
#include "GameBounds.h"
#include "GraphicsUtil.h"
#include "KeyboardInputMap.h"
#include "Textures.h"
#include "raymath.h"
#include <vector>

Scene::Scene(ECS::World* world, int numPlayers)
{
    Textures::Load();

    GameBounds::Init(world);

    Vector2 player1Position = Vector2{ (GAME_BOUNDS.width * 0.25f), (GAME_BOUNDS.height * 0.8f) };
    Entities::CreatePlayer(world, 0, player1Position, WHITE);
    if (numPlayers == 2) {
        Vector2 player2Position = Vector2{ (GAME_BOUNDS.width * 0.75f), (GAME_BOUNDS.height * 0.8f) };
        Entities::CreatePlayer(world, 1, player2Position, Color{ 70, 90, 100, 255 });
    }

    float enemyInitialY = (VIRTUAL_HEIGHT * 0.2 + SCOREBOARD_HEIGHT);
    Vector2 enemy1Position = Vector2{
        SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Vector2 enemy2Position = Vector2{
        VIRTUAL_WIDTH - SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Entities::CreateEnemy(world, enemy1Position);
    Entities::CreateEnemy(world, enemy2Position);
}

Scene::~Scene()
{
    Textures::Unload();
}

void Scene::Draw()
{
    GameBounds::Draw();
}
