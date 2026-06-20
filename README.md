# DeathRace

A C++ remake of Exidy's 1976 arcade classic **Death Race**, built with [raylib](https://www.raylib.com/) and an Entity-Component-System (ECS) architecture. Features retro CRT-style post-processing with authentic scanlines and bloom effects for that classic arcade feel.

Download the latest build for **Windows** and **macOS** at **[fabslab.itch.io/death-race](https://fabslab.itch.io/death-race)**.

![Death Race Marquee](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc2LnBuZw==/original/zAFTKi.png)

## Screenshots

| Gameplay | With Tombstones | Game Over |
|----------|-----------------|-----------|
| ![Gameplay](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc0LnBuZw==/original/9YfUnG.png) | ![Gameplay 2](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc1LnBuZw==/original/hDDQX1.png) | ![Game Over](https://img.itch.zone/aW1hZ2UvOTM5OTgvNDQxODc3LnBuZw==/original/0bkzC7.png) |

## Features

- Faithful remake of the 1976 arcade classic
- Local 2-player competitive mode
- Keyboard + game controller support (PS4, Xbox One, Xbox Wireless)
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

- [raylib](https://www.raylib.com/) 5.0
- C++17 compatible compiler
- **Windows:** Visual Studio 2022 (v143 toolset) or later
- **Linux/macOS:** CMake 3.14 or later

## Build Instructions

### Windows (Visual Studio)

The Visual Studio solution expects raylib as a sibling directory:

```
DeathRaceC/
  DeathRace/
    DeathRace.sln
    ...
raylib/
  src/
  ...
```

1. Clone this repository
2. Clone [raylib](https://github.com/raysan5/raylib) into a sibling `raylib/` directory
3. Open `DeathRace/DeathRace.sln` in Visual Studio 2022
4. Build and run (F5)

> **Note:** The `.vcxproj` is configured for the v143 toolset and latest Windows SDK. If you have an older Visual Studio version, you may need to retarget the solution.

### CMake (Windows, Linux, macOS)

The CMake build fetches raylib automatically via `FetchContent` — no manual raylib installation required.

```bash
# Clone the repository
git clone https://github.com/fabslab/DeathRaceC.git
cd DeathRaceC

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run (from the build directory so Content/ is found)
# Linux / macOS:
./DeathRace
# Windows:
Debug\DeathRace.exe
# or
Release\DeathRace.exe
```

> **Note:** The `Content/` directory (game assets) is copied to the build output directory automatically. You must run the executable from the build directory, or copy `Content/` manually to wherever you move the executable.

## Launch Options

Command-line arguments can be passed when launching the game:

| Option | Description |
|--------|-------------|
| `--windowed` | Start in windowed mode (default: fullscreen) |
| `--width <pixels>` | Set window width (default: 960) |
| `--height <pixels>` | Set window height (default: 720) |
| `--help`, `-h` | Show help message |

```bash
# Linux / macOS
./DeathRace --windowed
./DeathRace --windowed --width 1280 --height 960
./DeathRace --help

# Windows
Release\DeathRace.exe --windowed
Release\DeathRace.exe --windowed --width 1280 --height 960
Release\DeathRace.exe --help
```

While in-game, press **Alt+Enter** to toggle between windowed and fullscreen modes.

## Controls

### Player 1 (Keyboard — WASD)

| Action | Key |
|--------|-----|
| Accelerate | W |
| Turn Left | A |
| Turn Right | D |
| Reverse | S |

### Player 2 (Keyboard — Arrow Keys)

| Action | Key |
|--------|-----|
| Accelerate | Up Arrow |
| Turn Left | Left Arrow |
| Turn Right | Right Arrow |
| Reverse | Down Arrow |

### Controllers

Supported controllers are detected automatically by name:

- **PS4:** `Wireless Controller`
- **Xbox One (wired):** `Xbox Controller`
- **Xbox One (wireless):** `Xbox Wireless Controller`

Both controllers are supported for player movement and menu navigation.

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

Pre-built binaries are available on itch.io for **Windows** and **macOS**:

**[https://fabslab.itch.io/death-race](https://fabslab.itch.io/death-race)**

## Architecture

The game is built using an **Entity-Component-System (ECS)** pattern. The ECS world is managed by a lightweight header-only ECS library, with the following systems registered each frame:

- `PlayerMovementSystem` — Handles player input and vehicle movement
- `EnemyMovementSystem` — Controls AI-driven enemy vehicles
- `CollisionSystem` — Handles collisions between entities
- `RenderSystem` — Renders sprites and game objects
- `AnimationSystem` — Updates sprite animations
- `ScoreRenderSystem` — Displays the in-game scoreboard
- `MenuRenderSystem` — Renders menus and UI overlays
- `GameAudio` — Static audio loading / unloading helpers

## Credits

- **Original Game:** *Death Race* by Exidy (1976)
- **C++ Remake:** [@fabslab](https://github.com/fabslab)
- **ECS Header:** [ECS.h](DeathRace/ECS.h) by Sam Bloomberg (MIT License)

## License

This project is licensed under the **MIT License**.
