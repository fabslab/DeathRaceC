#pragma once

#include "ECS.h"
#include "raylib.h"

class Scene {
public:
    static void Load(ECS::World* world, int numPlayers);
    static void Unload(ECS::World* world);
};
