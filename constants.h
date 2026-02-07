#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window creation
constexpr int SCREEN_WIDTH  = 400;
constexpr int SCREEN_HEIGHT = 700;

// Grid dimensions (in cells)
constexpr int GRID_COLS = 10;
constexpr int GRID_ROWS = 20;

// Cell sizing
constexpr int CELL_SIZE = 30;

// Grid pixel size
constexpr int GRID_WIDTH  = GRID_COLS * CELL_SIZE;
constexpr int GRID_HEIGHT = GRID_ROWS * CELL_SIZE;

// Grid position (top-left)
constexpr int GRID_X = 50;
constexpr int GRID_Y = 80;

// Spawn position
constexpr int START_COL = 4;

#endif