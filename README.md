# Super Mario Bros NES C++ Remake

A Super Mario Bros NES-inspired platformer remake written entirely in C++ with
[raylib](https://www.raylib.com/). The project recreates classic Mario movement,
tile-based levels, enemies, power-ups, pipes, scorekeeping, and level transitions
using a small custom game loop and hand-authored level data.

## Features

- Classic side-scrolling Mario movement with walking, running, variable-height
  jumps, gravity, friction, and camera scrolling.
- Small, big, fire, invincibility, and star-powered Mario states.
- Coins, score popups, lives, level intro screens, timer, and HUD rendering.
- Question blocks, bricks, coin bricks, hidden blocks, shiny blocks, pipes,
  moving lifts, flagpoles, castles, and background props.
- Goombas, Koopas, Koopa shells, Piranha Plants, fireballs, mushrooms,
  fire flowers, stars, and 1-Up mushrooms.
- Multiple world areas registered through the level loader, including 1-1,
  1-1 subarea, 1-2 transitions/subareas, and 1-3.
- Debug tools for level editing and texture coordinate discovery.

## Requirements

- A C++17-capable compiler such as `g++` or `clang++`.
- `make`.
- raylib installed locally.

On macOS with Homebrew:

```sh
brew install raylib
```

The included `Makefile` assumes Homebrew's Apple Silicon paths:

```make
-I/opt/homebrew/include
-L/opt/homebrew/lib
```

If raylib is installed somewhere else, update `CXXFLAGS` and `LDFLAGS` in the
`Makefile`.

## Build and Run

From the repository root:

```sh
make
```

The default target builds `bin/main` and immediately runs it.

To build only the game executable:

```sh
make main
```

To run it after building:

```sh
./bin/main
```

To remove generated object files, dependency files, and binaries:

```sh
make clean
```

## Controls

| Action | Key |
| --- | --- |
| Start game | `Enter` |
| Move left | `A` |
| Move right | `D` |
| Run | `Left Shift` |
| Jump | `Space` |
| Shoot fireball | `F` |
| Enter pipe | `Down`/`S`, `Left`/`A`, or `Right`/`D` depending on pipe direction |

## Debug Tools

Build and run the level editor:

```sh
make editor
```

Build and run the texture finder:

```sh
make texture
```

The texture finder opens `assets/images/52570.png` by default. Change the
`texture` target in the `Makefile` to inspect another sprite sheet.

## Project Layout

```text
assets/
  fonts/              NES-style font asset
  images/             Sprite sheets and HUD image assets
include/              Header files for game systems and entities
include/blocks/       Block and tile entity headers
src/                  Main game implementation
src/blocks/           Block and tile entity implementations
tools/                Debug utilities
Makefile              Build targets for the game and debug tools
```

Important entry points:

- `src/main.cpp` owns the raylib window, main loop, state transitions, drawing,
  input handling, scoring, lives, and level reset flow.
- `src/mario.cpp` implements Mario movement, collisions, power-ups, fireballs,
  and animation state.
- `src/levelData.cpp` defines the hand-authored level layouts.
- `src/levelLoader.cpp` loads registered areas, rebuilds collision data, and
  manages camera/scene settings.

## Changing the Starting Level

The starting area is set in `src/main.cpp`:

```cpp
LevelAreaId startingArea = LevelAreaIds::Level11;
```

Available registered area IDs are declared in `include/levelData.h`:

- `LevelAreaIds::Level11`
- `LevelAreaIds::Level11Subarea`
- `LevelAreaIds::Level12Animation`
- `LevelAreaIds::Level12Underground`
- `LevelAreaIds::Level12Subarea`
- `LevelAreaIds::Level12Final`
- `LevelAreaIds::Level13`

Change `startingArea`, rebuild, and run the game again.

## Assets

The repository includes sprite sheets and a NES-style font under `assets/`.
The runtime loads these files by relative path, so run the executable from the
repository root unless you update the asset paths.

## Notes

This is a fan-made educational remake and is not affiliated with Nintendo.
All gameplay code in this repository is C++.
