#include "Scene.h"
#include "Constants.h"
#include "GraphicUtil.h"
#include "KeyboardInputMap.h"
#include "Player.h"
#include "PlayerInput.h"
#include "raymath.h"
#include <vector>

Scene::Scene()
{
    float sidewalkStartY = SCOREBOARD_HEIGHT + BORDER_WIDTH * 3;
    float sidewalkEndY = sidewalkStartY + GAME_BOUNDS.height - BORDER_WIDTH * 3;

    float sidewalkLeftX = SIDEWALK_WIDTH;
    float sidewalkRightX = GAME_BOUNDS.width - SIDEWALK_WIDTH;

    sidewalkLeftStartPos = { sidewalkLeftX, sidewalkStartY };
    sidewalkLeftEndPos = { sidewalkLeftX, sidewalkEndY };

    sidewalkRightStartPos = { sidewalkRightX, sidewalkStartY };
    sidewalkRightEndPos = { sidewalkRightX, sidewalkEndY };

    Vector2 player1Position = Vector2{ (GAME_BOUNDS.width * 0.25f), (GAME_BOUNDS.height * 0.8f) };
    Vector2 player2Position = Vector2{ (GAME_BOUNDS.width * 0.75f), (GAME_BOUNDS.height * 0.8f) };

    player1Input = new KeyboardPlayerInput(Input::PLAYER_LEFT);
    player2Input = new KeyboardPlayerInput(Input::PLAYER_RIGHT);

    player1 = new Player(player1Position, 0, { player1Input }, WHITE);
    player2 = new Player(player2Position, 1, { player2Input }, Color{ 70, 90, 100, 255 });

    float enemyInitialY = (VIRTUAL_HEIGHT * 0.2 + SCOREBOARD_HEIGHT);
    Vector2 enemy1Position = Vector2{
        SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    Vector2 enemy2Position = Vector2{
        VIRTUAL_WIDTH - SIDEWALK_WIDTH / 2,
        enemyInitialY
    };
    enemy1 = new Enemy(enemy1Position);
    enemy2 = new Enemy(enemy2Position);
}

Scene::~Scene()
{
    delete player1;
    delete player2;
    delete player1Input;
    delete player2Input;
    delete enemy1;
    delete enemy2;
}

void Scene::Update()
{
    player1->Update();
    player2->Update();
    enemy1->Update();
    enemy2->Update();
}

void Scene::Draw()
{
    DrawRectangleLinesEx(GAME_BOUNDS, BORDER_WIDTH, WHITE);

    GraphicUtil::DrawDottedLine(sidewalkLeftStartPos, sidewalkLeftEndPos, BORDER_WIDTH, WHITE);
    GraphicUtil::DrawDottedLine(sidewalkRightStartPos, sidewalkRightEndPos, BORDER_WIDTH, WHITE);

    player1->Draw();
    player2->Draw();
    enemy1->Draw();
    enemy2->Draw();
}
