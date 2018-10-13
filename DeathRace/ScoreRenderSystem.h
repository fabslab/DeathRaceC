#pragma once

#include "ECS.h"
#include "Events.h"
#include "PlayerIndex.h"

class ScoreRenderSystem
    : public ECS::EntitySystem,
      public ECS::EventSubscriber<Events::GameStateChangedEvent>,
      public ECS::EventSubscriber<Events::CollisionEnteredEvent> {
public:
    virtual void configure(ECS::World* world) override;
    virtual void unconfigure(ECS::World* world) override;
    void receive(ECS::World* world, const Events::GameStateChangedEvent& event) override;
    void receive(ECS::World* world, const Events::CollisionEnteredEvent& event) override;
    virtual void tick(ECS::World* world, float deltaTime) override;

private:
    void Update(ECS::World* world, float deltaTime);
    void Draw();
    void Reset();

    std::string IntToDisplayString(int num);
    void SetScore(PlayerIndex playerIndex, int score);
    void KillEnemy(ECS::World* world, ECS::Entity* enemy, ECS::Entity* player);
    float gameTime;
    int player1Score;
    int player2Score;
};
