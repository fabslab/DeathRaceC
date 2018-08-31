#include "Scene.h"
#include "Constants.h"
#include "GameBounds.h"
#include "GraphicUtil.h"
#include "KeyboardInputMap.h"
#include "Player.h"
#include "Textures.h"
#include "raymath.h"
#include <vector>

Scene::Scene(ECS::World* world, int numPlayers)
{
    Textures::Load();

    GameBounds::Init(world);

    Vector2 player1Position = Vector2{ (GAME_BOUNDS.width * 0.25f), (GAME_BOUNDS.height * 0.8f) };
    player1 = new Player(world->create(), 0, player1Position, WHITE);
    if (numPlayers == 2) {
        Vector2 player2Position = Vector2{ (GAME_BOUNDS.width * 0.75f), (GAME_BOUNDS.height * 0.8f) };
        player2 = new Player(world->create(), 1, player2Position, Color{ 70, 90, 100, 255 });
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
    enemy1 = new Enemy(world->create(), enemy1Position);
    enemy2 = new Enemy(world->create(), enemy2Position);
}

Scene::~Scene()
{
    delete player1;
    if (player2 != nullptr) {
        delete player2;
    }
    delete enemy1;
    delete enemy2;
    Textures::Unload();
}

void Scene::Draw()
{
    GameBounds::Draw();
}
