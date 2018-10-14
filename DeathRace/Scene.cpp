#include "Scene.h"
#include "Entities.h"
#include "GameBounds.h"
#include "GameConstants.h"
#include "PlayerIndex.h"

void Scene::Load(ECS::World* world, int numPlayers)
{
    GameBounds::Load(world);

    Vector2 player1Position = Vector2 { (GameConstants::GAME_BOUNDS.width * 0.25f), (GameConstants::GAME_BOUNDS.height * 0.8f) };
    Entities::CreatePlayer(world, PlayerIndex::One, player1Position, WHITE);
    if (numPlayers == 2) {
        Vector2 player2Position = Vector2 { (GameConstants::GAME_BOUNDS.width * 0.75f), (GameConstants::GAME_BOUNDS.height * 0.8f) };
        Entities::CreatePlayer(world, PlayerIndex::Two, player2Position, Color { 70, 90, 100, 255 });
    }

    float enemyInitialY = (GameConstants::VIRTUAL_HEIGHT * 0.2 + GameConstants::SCOREBOARD_HEIGHT);
    Vector2 enemy1Position = Vector2 {
        GameConstants::SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Vector2 enemy2Position = Vector2 {
        GameConstants::VIRTUAL_WIDTH - GameConstants::SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Entities::CreateEnemy(world, enemy1Position);
    Entities::CreateEnemy(world, enemy2Position);
}

void Scene::Unload(ECS::World* world)
{
    world->all([&](ECS::Entity* entity) {
        world->destroy(entity);
    });
}
