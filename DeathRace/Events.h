#pragma once

#include "ECS.h"
#include "GameState.h"
#include <vector>

namespace Events {
typedef struct CollisionEnteredEvent {
    size_t firstEntity;
    size_t secondEntity;
} CollisionEnteredEvent;

typedef struct GameStateChangedEvent {
    GameState state;
    std::vector<int> scores;
} GameStateChangedEvent;

typedef struct NumberOfPlayersChanged {
    int numberOfPlayers;
} NumberOfPlayersChanged;
}
