#pragma once

#include "ECS.h"
#include "GameState.h"
#include <vector>

namespace Events {
typedef struct CollisionEnteredEvent {
    ECS::Entity* firstEntity = nullptr;
    ECS::Entity* secondEntity = nullptr;
} CollisionEnteredEvent;

typedef struct GameStateChangedEvent {
    GameState state;
    std::vector<int> scores;
} GameStateChangedEvent;

typedef struct NumberOfPlayersChanged {
    int numberOfPlayers;
} NumberOfPlayersChanged;
}
