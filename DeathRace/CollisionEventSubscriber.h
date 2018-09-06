#pragma once

#include "ECS.h"
#include "Events.h"

class CollisionEventSubscriber : public ECS::EventSubscriber<Events::CollisionEvent> {
public:
    virtual void receive(ECS::World* world, const Events::CollisionEvent& event) override;
};
