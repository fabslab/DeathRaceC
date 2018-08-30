#pragma once

#include "ECS.h"
#include "Enemy.h"
#include "KeyboardPlayerInput.h"
#include "Player.h"
#include "raylib.h"

class Scene {
public:
    Scene(ECS::World* world, int numPlayers);
    ~Scene();
    void Draw();

private:
    Vector2 sidewalkLeftStartPos, sidewalkLeftEndPos, sidewalkRightStartPos, sidewalkRightEndPos;
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    Enemy *enemy1, *enemy2;
    KeyboardPlayerInput *player1Input, *player2Input;
    ECS::World* world;
};
