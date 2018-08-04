#pragma once

#include "raylib.h"
#include "Player.h"
#include "KeyboardPlayerInput.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Draw();
	void Update();
private:
	const int SCOREBOARD_HEIGHT = 30;
	const int SIDEWALK_WIDTH = 32;
	const int BORDER_WIDTH = 2;
	Rectangle border;
	Vector2 sidewalkLeftStartPos, sidewalkLeftEndPos, sidewalkRightStartPos, sidewalkRightEndPos;
	Player *player1, *player2;
	KeyboardPlayerInput *player1Input, *player2Input;
	void DrawDottedLine(Vector2 startPos, Vector2 endPos, int thickness, Color color);
};

