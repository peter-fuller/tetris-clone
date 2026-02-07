# Tetris Clone

A fully functional tetris game built in C++ using SDL2

## Features

- 7 classic shapes
- Piece rotation with wall kick mechanics
- Collision detection
- Line clearing
- Hard drop (spacebar)
- Gravity

## Technologies Used

- C++17
- SDL2 (graphics and input handling)
- WSL2/Linux development environment

## Building and Running

### Prerequisites
```bash
sudo apt update
sudo apt install build-essential libsdl2-dev
```

### Compile
```bash
make
```

### Run
```bash
./tetris
```

## Controls

- **Left/Right Arrow**: Move piece
- **Up Arrow**: Rotate piece
- **Down Arrow**: Soft drop
- **Spacebar**: Hard drop

## Project Structure

- `main.cpp` - Game loop and SDL initialization
- `game.cpp/h` - Core game logic (collision, gravity, line clearing)
- `pieces.cpp/h` - Piece definitions and spawning
- `constants.h` - Game constants (grid size, colors, etc.)

## Implementation Highlights

- Matrix-based piece rotation with 90-degree clockwise transforms
- Bottom-to-top line clearing algorithm with automatic grid shifting
- Collision system checking both boundaries and locked piece positions
- Refactored architecture following separation of concerns

---

Built by Peter Fuller as a C++ learning project.