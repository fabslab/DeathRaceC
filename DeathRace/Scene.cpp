#include "Scene.h"
#include "Constants.h"
#include "raymath.h"


Scene::Scene()
{
	border = { 0, (float)SCOREBOARD_HEIGHT, VIRTUAL_WIDTH, (float)(VIRTUAL_HEIGHT - SCOREBOARD_HEIGHT) };

	float sidewalkStartY = SCOREBOARD_HEIGHT + BORDER_WIDTH * 3;
	float sidewalkEndY = sidewalkStartY + border.height - BORDER_WIDTH * 3;

	float sidewalkLeftX = SIDEWALK_WIDTH;
	float sidewalkRightX = border.width - SIDEWALK_WIDTH;

	sidewalkLeftStartPos = { sidewalkLeftX, sidewalkStartY };
	sidewalkLeftEndPos = { sidewalkLeftX, sidewalkEndY };

	sidewalkRightStartPos = { sidewalkRightX, sidewalkStartY };
	sidewalkRightEndPos = { sidewalkRightX, sidewalkEndY };
}

Scene::~Scene()
{
}

void Scene::Draw()
{
	DrawRectangleLinesEx(border, BORDER_WIDTH, WHITE);

	DrawDottedLine(sidewalkLeftStartPos, sidewalkLeftEndPos, BORDER_WIDTH, WHITE);
	DrawDottedLine(sidewalkRightStartPos, sidewalkRightEndPos, BORDER_WIDTH, WHITE);
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
