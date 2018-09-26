#pragma once

#include "ECS.h"
#include "PlayerIndex.h"

class ScoreRenderSystem : public ECS::EntitySystem {
public:
    ScoreRenderSystem(float gameTime);
    virtual void tick(ECS::World* world, float deltaTime) override;
    void SetGameTime(float gameTime);

private:
    void Update(ECS::World* world, float deltaTime);
    void Draw();

    std::string IntToDisplayString(int num);
    void SetScore(PlayerIndex playerIndex, int score);
    float gameTime;
    int player1Score = -1;
    int player2Score = -1;
};
