#include "Scene.h"
#include "Constants.h"
#include "raymath.h"
#include "Player.h"
#include "KeyboardInputMap.h"
#include "PlayerInput.h"
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

	Vector2 player1Position = { (int)(GAME_BOUNDS.width * 0.25), (int)(GAME_BOUNDS.height * 0.8) };
	Vector2 player2Position = { (int)(GAME_BOUNDS.width * 0.75), (int)(GAME_BOUNDS.height * 0.8) };

	player1Input = new KeyboardPlayerInput(Input::Keyboard::PLAYER_LEFT);
	player2Input = new KeyboardPlayerInput(Input::Keyboard::PLAYER_RIGHT);

	player1 = new Player(player1Position, 0, { player1Input }, WHITE);
	player2 = new Player(player2Position, 1, { player2Input }, Color{ 70, 90, 100, 255 });
}

Scene::~Scene()
{
	delete player1;
	delete player2;
	delete player1Input;
	delete player2Input;
}

void Scene::Update()
{
	player1->Update();
	player2->Update();
}

void Scene::Draw()
{
	DrawRectangleLinesEx(GAME_BOUNDS, BORDER_WIDTH, WHITE);

	DrawDottedLine(sidewalkLeftStartPos, sidewalkLeftEndPos, BORDER_WIDTH, WHITE);
	DrawDottedLine(sidewalkRightStartPos, sidewalkRightEndPos, BORDER_WIDTH, WHITE);

	player1->Draw();
	player2->Draw();
}

void Scene::DrawDottedLine(Vector2 startPos, Vector2 endPos, int thickness, Color color)
{
	Vector2 dashStart = Vector2(startPos);
	Vector2 dash = Vector2Scale(Vector2Normalize(Vector2Subtract(endPos, startPos)), thickness);
	Vector2 dashEnd = Vector2Add(dashStart, dash);

	while (dashEnd.x <= endPos.x && dashEnd.y <= endPos.y) {
		DrawLineEx(dashStart, dashEnd, thickness, color);
		dashStart = Vector2Add(dashEnd, Vector2Scale(dash, 2));
		dashEnd = Vector2Add(dashStart, dash);
	}
}
