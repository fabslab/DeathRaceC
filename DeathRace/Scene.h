#pragma once

#include "raylib.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Draw();
private:
	const int SCOREBOARD_HEIGHT = 30;
	const int SIDEWALK_WIDTH = 32;
	const int BORDER_WIDTH = 2;
	Rectangle border;
	Vector2 sidewalkLeftStartPos, sidewalkLeftEndPos, sidewalkRightStartPos, sidewalkRightEndPos;
	void DrawDottedLine(Vector2 startPos, Vector2 endPos, int thickness, Color color);
};

