#pragma once

#include "ECS.h"

class ScoreRenderSystem : public ECS::EntitySystem {
public:
    ScoreRenderSystem(float gameTime);
    virtual void tick(ECS::World* world, float deltaTime) override;
    void SetGameTime(float gameTime);

private:
    std::string IntToDisplayString(int num);
    float gameTime;
};
