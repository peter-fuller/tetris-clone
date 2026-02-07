#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>

struct Piece;

// Functions
void lockPiece(Piece& activePiece, std::vector<std::vector<int>>& gameGrid);
void renderLockedPieces(SDL_Renderer* render, const std::vector<std::vector<int>>& gameGrid);
void renderGrid(SDL_Renderer* render);
void renderActivePiece(SDL_Renderer* render, Piece& activePiece);
void clearLines(std::vector<std::vector<int>>& gameGrid);
void rotatePiece(Piece& activePiece, const std::vector<std::vector<int>>& gameGrid);

bool applyGravity(Piece& activePiece, Uint32& lastDropTime, Uint32 dropInterval, std::vector<std::vector<int>>& gameGrid);
bool checkCollision(int newX, int newY, const Piece& activePiece, const std::vector<std::vector<int>>& gameGrid);
bool handleGameOver(SDL_Renderer* render, const std::vector<std::vector<int>>& gameGrid);

int handleInput(Piece& activePiece, std::vector<std::vector<int>>& gameGrid);

Piece spawnRandomPiece();


#endif