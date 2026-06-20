# DeathRaceC

A C++17 remake of Exidy's 1976 arcade classic **Death Race**, built with [Raylib](https://www.raylib.com/) and an Entity-Component-System (ECS) architecture. Features retro CRT-style post-processing with authentic scanlines and bloom effects for that classic arcade feel.

Play the latest build online at: **[fabslab.itch.io/death-race](https://fabslab.itch.io/death-race)**

![Death Race Marquee](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc2LnBuZw==/original/zAFTKi.png)

## Screenshots

| Gameplay | With Tombstones | Game Over |
|----------|-----------------|-----------|
| ![Gameplay](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc0LnBuZw==/original/9YfUnG.png) | ![Gameplay 2](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc1LnBuZw==/original/hDDQX1.png) | ![Game Over](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc3LnBuZw==/original/0bkzC7.png) |

## Features

- Faithful remake of the 1976 arcade classic
- Local 2-player competitive mode
- Keyboard + game controller support (PS4, Xbox One)
- Authentic CRT post-processing (scanlines + bloom)
- Retro pixel art style with virtual 480x360 resolution
- Windowed mode with **Alt+Enter** fullscreen toggle
- Command-line launch options for resolution and display mode

## About the Game

One of the most controversial games of its time has been remade for PC!

Death Race pits the player against evasive, running Gremlins. The object of the game is simple. Hit a Gremlin when they've ventured onto the road and you win a point. Crash into one of their tombstones you've created and you're stuck for a second unless you hit reverse and start back up!

Each game causes its own maze of crosses that players must steer through. The more kills, the more crosses; the more crosses, the harder the steering becomes. As your skill increases it becomes more difficult to maneuver but the Gremlins also become constrained by the maze of crosses. Master switching into reverse and back to build up a high score.

This is a fan implementation of the original cabinet arcade game made by Exidy in 1976, updated to play on today's computers. The original is now rare and with no emulation seemingly possible, this PC version has been released for anyone struggling to find it and get their Death Race fix.

[Background info on the original game](https://en.wikipedia.org/wiki/Death_Race_(1976_video_game))

## Dependencies

- [Raylib](https://www.raylib.com/) (4.x or later recommended)
- Visual Studio 2019 or later (Windows)
- C++17 compatible compiler

## Build Instructions

### Windows (Visual Studio)

1. Clone the repository
2. Open `DeathRace.sln` in Visual Studio
3. Ensure raylib is installed and include/lib paths are configured
4. Build and run (F5)

### Linux / macOS (CMake)

```bash
# Clone the repository
git clone https://github.com/fabslab/DeathRaceC.git
cd DeathRaceC

# Build with CMake
mkdir build && cd build
cmake ..
cmake --build .

# Run
./DeathRace
```

> **Note:** The CMake build fetches Raylib automatically via FetchContent.

## Launch Options

Command-line arguments can be passed when launching the game:

| Option | Description |
|--------|-------------|
| `--windowed` | Start in windowed mode (default: fullscreen) |
| `--width <pixels>` | Set window width (default: 960) |
| `--height <pixels>` | Set window height (default: 720) |
| `--help`, `-h` | Show help message |

```bash
# Examples
./DeathRace --windowed
./DeathRace --windowed --width 1280 --height 960
./DeathRace --help
```

While in-game, press **Alt+Enter** to toggle between windowed and fullscreen modes.

## Controls

### Player 1 (Keyboard - WASD)

| Action     | Key |
|------------|-----|
| Accelerate | W   |
| Turn Left  | A   |
| Turn Right | D   |
| Reverse    | S   |

### Player 2 (Keyboard - Arrow Keys)

| Action     | Key        |
|------------|------------|
| Accelerate | Up Arrow   |
| Turn Left  | Left Arrow |
| Turn Right | Right Arrow|
| Reverse    | Down Arrow |

### Controllers

Both PS4 and Xbox One controllers are supported for player movement and menu navigation.

### Menu Navigation

- **Arrow Keys** + **Enter** to select
- **Escape** to go back / pause

## How to Play

- Each round lasts **99 seconds**
- Run over gremlins to score points
- Avoid tombstones and other cars
- The player with the highest score at the end wins!
- Press **Alt+Enter** at any time to toggle fullscreen

## Download

Pre-built binaries are available on itch.io for **Windows** and **Mac**:

**[https://fabslab.itch.io/death-race](https://fabslab.itch.io/death-race)**

You can also play directly in your browser on the itch.io page.

## Architecture

The game is built using an **Entity-Component-System (ECS)** pattern. The ECS world is managed by a lightweight header-only ECS library, with the following systems registered each frame:

- `PlayerMovementSystem` — Handles player input and vehicle movement
- `EnemyMovementSystem` — Controls AI-driven enemy vehicles
- `CollisionSystem` — Handles collisions between entities
- `RenderSystem` — Renders sprites and game objects
- `AnimationSystem` — Updates sprite animations
- `ScoreRenderSystem` — Displays the in-game scoreboard
- `MenuRenderSystem` — Renders menus and UI overlays

## Credits

- **Original Game:** *Death Race* by Exidy (1976)
- **C++ Remake:** [@fabslab](https://github.com/fabslab)
- **ECS Header:** [ECS.h](DeathRace/ECS.h) by Sam Bloomberg (MIT License)

## License

This project is licensed under the **MIT License**.

The ECS header (`ECS.h`) is Copyright (c) 2016 Sam Bloomberg and is used under the MIT License. See the file header for full license text.
