#ifndef PIECES_H
#define PIECES_H
#include <vector>
#include <SDL2/SDL.h>
#include "constants.h"

struct Piece {
    std::vector<std::vector<int>> shape;
    int x, y;
    Uint8 r, g, b;

    Piece() { 
        x = GRID_X + (START_COL * CELL_SIZE);
        y = GRID_Y;
    }
};


Piece createOPiece();
Piece createIPiece();
Piece createTPiece();
Piece createLPiece();
Piece createJPiece();
Piece createSPiece();
Piece createZPiece();


#endif