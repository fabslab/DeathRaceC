#pragma once

#include "ECS.h"
#include "KeyboardPlayerInput.h"
#include "raylib.h"

class Scene {
public:
    Scene(ECS::World* world, int numPlayers);
    void Draw();
    static Scene* GetCurrentScene();
    static void SetCurrentScene(Scene* scene);
    static void UnloadCurrentScene();

private:
    static Scene* currentScene;
};
