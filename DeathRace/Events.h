#pragma once

#include "ECS.h"
#include "GameState.h"

namespace Events {
typedef struct CollisionEnteredEvent {
    ECS::Entity* firstEntity = nullptr;
    ECS::Entity* secondEntity = nullptr;
} CollisionEnteredEvent;

typedef struct GameStateChangedEvent {
    GameState state;
} GameStateChangedEvent;

typedef struct NumberOfPlayersChanged {
    int numberOfPlayers;
} NumberOfPlayersChanged;
}
