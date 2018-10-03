#pragma once

#include "ECS.h"
#include "GameState.h"

namespace Events {
typedef struct CollisionEvent {
    ECS::Entity* firstEntity = nullptr;
    ECS::Entity* secondEntity = nullptr;
} CollisionEvent;

typedef struct GameStateChangedEvent {
    GameState state;
} GameStateChangedEvent;

typedef struct NumberOfPlayersChanged {
    int numberOfPlayers;
} NumberOfPlayersChanged;
}
