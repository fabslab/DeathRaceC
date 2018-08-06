#pragma once

#include "Enemy.h"
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
    Enemy *enemy1, *enemy2;
    KeyboardPlayerInput *player1Input, *player2Input;
};
