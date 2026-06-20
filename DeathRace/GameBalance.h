#pragma once

namespace Balance {
    // Enemy movement
    constexpr float ENEMY_SPEED = 1.5f;
    constexpr float ENEMY_TURN_TIME_MIN_MS = 350.f;
    constexpr float ENEMY_TURN_TIME_MAX_MS = 1800.f;
    constexpr float ENEMY_TURN_CHANCE = 0.05f;

    // Enemy collision
    constexpr float ENEMY_COLLISION_WIDTH = 14.f;
    constexpr float ENEMY_COLLISION_HEIGHT = 15.f;

    // Enemy animation
    constexpr int ENEMY_ANIMATION_FRAMES = 2;
    constexpr float ENEMY_ANIMATION_FRAME_DURATION_MS = 60.f;

    // Player movement
    constexpr float PLAYER_FORWARD_SPEED = 2.f;
    constexpr float PLAYER_REVERSE_SPEED = 1.f;
    constexpr float PLAYER_SPEED_WHILE_COLLIDING = 0.5f;
    constexpr float PLAYER_CRASH_DURATION_MS = 1000.f;

    // Player collision
    constexpr float PLAYER_COLLISION_WIDTH = 12.f;
    constexpr float PLAYER_COLLISION_HEIGHT = 16.f;

    // Player rotation
    constexpr float PLAYER_MAX_TURN_ANGLE_PER_UPDATE = PI / 48;
    constexpr float PLAYER_SNAP_ANGLE = PI / 8;

    // Tombstone collision
    constexpr float TOMBSTONE_COLLISION_WIDTH = 9.f;
    constexpr float TOMBSTONE_COLLISION_HEIGHT = 14.f;
}
