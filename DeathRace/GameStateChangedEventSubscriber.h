#pragma once

#include "ECS.h"
#include "Events.h"
#include "GameState.h"

class GameStateChangedEventSubscriber : public ECS::EventSubscriber<Events::GameStateChangedEvent> {
public:
    virtual void receive(ECS::World* world, const Events::GameStateChangedEvent& event) override;
    static GameState GetGameState();

private:
    static GameState gameState;
};
