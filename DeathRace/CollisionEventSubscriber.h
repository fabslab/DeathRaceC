#pragma once

#include "ECS.h"
#include "Events.h"

class CollisionEventSubscriber : public ECS::EventSubscriber<Events::CollisionEnteredEvent> {
public:
    virtual void receive(ECS::World* world, const Events::CollisionEnteredEvent& event) override;

private:
    void KillEnemy(ECS::World* world, ECS::Entity* enemy, ECS::Entity* player);
};
