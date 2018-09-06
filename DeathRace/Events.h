#pragma once

#include "ECS.h"

namespace Events {
typedef struct CollisionEvent {
    ECS::Entity* firstEntity = nullptr;
    ECS::Entity* secondEntity = nullptr;
} CollisionEvent;
}
