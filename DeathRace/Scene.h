#pragma once

#include "ECS.h"
#include "KeyboardPlayerInput.h"
#include "raylib.h"

class Scene {
public:
    Scene(ECS::World* world, int numPlayers);
    ~Scene();
    void Draw();

private:
    ECS::World* world;
};
