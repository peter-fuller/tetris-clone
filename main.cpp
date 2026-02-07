#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "pieces.h"
#include "constants.h"


int main(int argc, char* argv[]) {

    // Create the window
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("block game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    
    // Time intervals for gravity
    Uint32 lastDropTime = SDL_GetTicks();
    Uint32 dropInterval = 500;

    // Vector for the grid and previous state grid
    std::vector<std::vector<int>> gameGrid(GRID_ROWS, std::vector<int>(GRID_COLS, 0)); 

    // Game loop and seed the RNG
    bool running = true;
    srand(time(NULL));
    Piece activePiece = spawnRandomPiece();

    while (running) {

        int inputResult = handleInput(activePiece, gameGrid); // 0 = Continue, 1 = Quit, 2 = Game Over
        if (inputResult == 1) {
            running = false;
        }
        if (inputResult == 2) {
            handleGameOver(render, gameGrid);
            break;
        }

        if (applyGravity(activePiece, lastDropTime, dropInterval, gameGrid)) {
            handleGameOver(render, gameGrid);
            break;
        }

        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);     
        renderGrid(render);
        renderLockedPieces(render, gameGrid);
        renderActivePiece(render, activePiece);       
        clearLines(gameGrid);
        SDL_RenderPresent(render);

    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}