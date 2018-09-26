#pragma once

#include "ECS.h"
#include "raylib.h"

// TODO: rename this SceneLoader once all static methods
class Scene {
public:
    Scene(ECS::World* world, int numPlayers);
    ~Scene();
    void Draw();
    static Scene* GetCurrentScene();
    static void SetCurrentScene(Scene* scene);
    static void UnloadCurrentScene();

private:
    static Scene* currentScene;
    ECS::World* world;
};
