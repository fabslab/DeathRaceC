#pragma once

#include "KeyboardPlayerInput.h"
#include "Player.h"
#include "raylib.h"

class Scene {
public:
    Scene();
    ~Scene();
    void Draw();
    void Update();

private:
    Vector2 sidewalkLeftStartPos, sidewalkLeftEndPos, sidewalkRightStartPos, sidewalkRightEndPos;
    Player *player1, *player2;
    KeyboardPlayerInput *player1Input, *player2Input;
    void DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color);
};
