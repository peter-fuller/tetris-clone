#include "game.h"
#include "pieces.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void lockPiece(Piece& activePiece, std::vector<std::vector<int>>& gameGrid) {
    // Avoid type compiler warnings
    int pieceRows = static_cast<int>(activePiece.shape.size());
    int pieceCols = static_cast<int>(activePiece.shape[0].size());
    
    // Grid offsets
    int col = (activePiece.x - GRID_X) / CELL_SIZE;
    int row = (activePiece.y - GRID_Y) / CELL_SIZE;

    // Lock the piece on gameGrid
    for (int i = 0; i < pieceRows; i++) {
        for (int j = 0; j < pieceCols; j++) {
            if (activePiece.shape[i][j] >= 1) {
                gameGrid[row + i][col + j] = activePiece.shape[i][j];
            }
        }
    }

    // Reset the piece position to row 0, col 4
    activePiece.x = GRID_X + (START_COL * CELL_SIZE);
    activePiece.y = GRID_Y;
}

void renderLockedPieces(SDL_Renderer* render, const std::vector<std::vector<int>>& gameGrid) {
    // Find the position of locked cells
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (gameGrid[i][j] >= 1) {
                int x = GRID_X + (j * CELL_SIZE); 
                int y = GRID_Y + (i * CELL_SIZE);

                SDL_Rect cell{x, y, CELL_SIZE, CELL_SIZE};
                Uint8 r, g, b;
                switch(gameGrid[i][j]) {
                    case 1: r = 255; g = 255; b = 0; break; // O piece color
                    case 2: r = 0; g = 255; b = 255; break; // I piece color 
                    case 3: r = 128; g = 0; b = 128; break; // T piece color
                    case 4: r = 255; g = 165; b = 0; break; // L piece color
                    case 5: r = 0; g = 0; b = 255; break; // J piece color
                    case 6: r = 0; g = 255; b = 0; break; // S piece color
                    case 7: r = 255; g = 0; b = 0; break; // Z piece color
                }
                // Fill the cell
                SDL_SetRenderDrawColor(render, r, g, b, 255);
                SDL_RenderFillRect(render, &cell);

                // Draw outline
                SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                SDL_RenderDrawRect(render, &cell);
            }
        }
    }
}

void renderGrid(SDL_Renderer* render) {
    // Playing field
    SDL_Rect gridRect;
    gridRect.w = GRID_WIDTH;
    gridRect.h = GRID_HEIGHT;
    gridRect.x = GRID_X;
    gridRect.y = GRID_Y;        
    SDL_SetRenderDrawColor(render, 45, 45, 45, 255);
    SDL_RenderFillRect(render, &gridRect);


    // Columns
    SDL_SetRenderDrawColor(render, 0, 0, 0, 200);

    for (int i = 0; i <= GRID_COLS; i++) {
        int x = GRID_X + (i * CELL_SIZE);
        SDL_RenderDrawLine(render, x, GRID_Y, x, GRID_Y + GRID_HEIGHT);
    }

    // Rows
    for (int i = 0; i <= GRID_ROWS; i++) {
        int y = GRID_Y + (i * CELL_SIZE);
        SDL_RenderDrawLine(render, GRID_X, y, GRID_X + GRID_WIDTH, y);
    }
}

void renderActivePiece(SDL_Renderer* render, Piece& activePiece) {
    // Avoid type compiler warnings
    int pieceRows = static_cast<int>(activePiece.shape.size());
    int pieceCols = static_cast<int>(activePiece.shape[0].size());

    for (int i = 0; i < pieceRows; i++) {
        for (int j = 0; j < pieceCols; j++) {
            if (activePiece.shape[i][j] >= 1) {
                SDL_Rect cell;
                cell.x = activePiece.x + (j * CELL_SIZE);
                cell.y = activePiece.y + (i * CELL_SIZE);
                cell.w = CELL_SIZE;
                cell.h = CELL_SIZE;

                // Fill the cell
                SDL_SetRenderDrawColor(render, activePiece.r, activePiece.g, activePiece.b, 255);
                SDL_RenderFillRect(render, &cell);

                // Draw outline
                SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                SDL_RenderDrawRect(render, &cell);
            }
        }
    }
}

void clearLines(std::vector<std::vector<int>>& gameGrid) {
    // Avoid type compiler warnings
    int totalRows = static_cast<int>(gameGrid.size());
    int totalCols = static_cast<int>(gameGrid[0].size());
    
    // Check bottom to top
    for (int row = totalRows - 1; row >= 0; row--) {
        bool needsRecheck = true;

        // Check each cell in the row
        while (needsRecheck) {
            bool isFull = true;
            for (int col = 0; col < totalCols; col++) {
                if (gameGrid[row][col] == 0) {
                    isFull = false;
                    break;
                }
            }

            // If row is full, shift everything down 1
            if (isFull) {
                for (int shiftRow = row; shiftRow > 0; shiftRow--) {
                    for (int col = 0; col < totalCols; col++) {
                        gameGrid[shiftRow][col] = gameGrid[shiftRow - 1][col];
                    }
                }

                // Add one row of 0's are the top
                for (int col = 0; col < totalCols; col++)
                    gameGrid[0][col] = 0;
            } 
            else {
                needsRecheck = false;
            }
        }
    }
}

void rotatePiece(Piece& activePiece, const std::vector<std::vector<int>>& gameGrid) {
    // Avoid type compiler warnings
    int pieceRows = static_cast<int>(activePiece.shape.size());
    int pieceCols = static_cast<int>(activePiece.shape[0].size());
    auto oldShape = activePiece.shape;
    std::vector<std::vector<int>> newShape(pieceRows, std::vector<int>(pieceCols, 0));

    // Rotate the piece
    for (int i = 0; i < pieceRows; i++) {
        for (int j = 0; j < pieceCols; j++) {
            newShape[j][pieceRows - 1 - i] = oldShape[i][j];
        }
    }
    
    activePiece.shape = newShape;

    // Collision check that rotated piece and adjust accordingly
    if (!checkCollision(activePiece.x, activePiece.y, activePiece, gameGrid)) {
        return;
    }
    if (!checkCollision(activePiece.x - CELL_SIZE, activePiece.y, activePiece, gameGrid)) {
        activePiece.x -= CELL_SIZE;
        return;
    }
    if (!checkCollision(activePiece.x + CELL_SIZE, activePiece.y, activePiece, gameGrid)) {
        activePiece.x += CELL_SIZE;
        return;
    }
    if (!checkCollision(activePiece.x - 2 * CELL_SIZE, activePiece.y, activePiece, gameGrid)) {
        activePiece.x -= 2 * CELL_SIZE;
        return;
    }
    if (!checkCollision(activePiece.x + 2 * CELL_SIZE, activePiece.y, activePiece, gameGrid)) {
        activePiece.x += 2 * CELL_SIZE;
        return;
    }

    // If every conditional returns false, return to old shape
    activePiece.shape = oldShape;
}

bool applyGravity(Piece& activePiece, Uint32& lastDropTime, Uint32 dropInterval, std::vector<std::vector<int>>& gameGrid) {
    Uint32 currentTime = SDL_GetTicks();

    // Drop the piece one cell at a time
    if (currentTime - lastDropTime >= dropInterval) {
        if (!checkCollision(activePiece.x, activePiece.y + CELL_SIZE, activePiece, gameGrid)) {
            activePiece.y += CELL_SIZE;
        }
        else {
            lockPiece(activePiece, gameGrid);
            activePiece = spawnRandomPiece();
            if (checkCollision(activePiece.x, activePiece.y, activePiece, gameGrid)) {
                return true; // Game over check
            }
        }
        lastDropTime = currentTime;
    }

    return false;
}

bool checkCollision(int newX, int newY, const Piece& activePiece, const std::vector<std::vector<int>>& gameGrid) {
    // Visual offsets
    int col = (newX - GRID_X) / CELL_SIZE;
    int row = (newY - GRID_Y) / CELL_SIZE;

    for (size_t i = 0; i < activePiece.shape.size(); i++) {
        for (size_t j = 0; j < activePiece.shape[i].size(); j++) {
            if (activePiece.shape[i][j] >= 1) {
                int checkRow = row + i;
                int checkColumn = col + j;

                if (checkRow < 0 || checkRow >= GRID_ROWS || checkColumn < 0 || checkColumn >= GRID_COLS) {
                    return true;
                }

                if (gameGrid[checkRow][checkColumn] >= 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool handleGameOver(SDL_Renderer* render, const std::vector<std::vector<int>>& gameGrid) {
    // Render the frozen game state in background
    SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
    SDL_RenderClear(render);
    renderGrid(render);
    renderLockedPieces(render, gameGrid);
    
    // Draw a box indicating game over
    SDL_SetRenderDrawColor(render, 150, 0, 0, 255);
    SDL_Rect gameOverBox = {GRID_X + 50, GRID_Y + 250, 200, 100};
    SDL_RenderFillRect(render, &gameOverBox);
    
    SDL_RenderPresent(render);
    
    // Wait for user input
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;  // Close game
            }
            if (event.type == SDL_KEYDOWN) {
                return false;  // Any key closes game
            }
        }
        SDL_Delay(16);  // ~60 FPS while waiting
    }
}

int handleInput(Piece& activePiece, std::vector<std::vector<int>>& gameGrid) {
    // Track events in a queue
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 1;
    
        // Move the piece
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_LEFT) {
                if (!checkCollision(activePiece.x - CELL_SIZE, activePiece.y, activePiece, gameGrid)) { // Left wall check
                    activePiece.x -= CELL_SIZE;
                }
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                if (!checkCollision(activePiece.x + CELL_SIZE, activePiece.y, activePiece, gameGrid)) { // Right wall check
                    activePiece.x += CELL_SIZE;
                }
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                rotatePiece(activePiece, gameGrid);
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                if (!checkCollision(activePiece.x, activePiece.y + CELL_SIZE, activePiece, gameGrid)) {
                    activePiece.y += CELL_SIZE;
                }
                else {
                    lockPiece(activePiece, gameGrid);
                    activePiece = spawnRandomPiece();
                } 
            }
            else if (event.key.keysym.sym == SDLK_SPACE) { 
                while (!checkCollision(activePiece.x, activePiece.y + CELL_SIZE, activePiece, gameGrid)) {
                    activePiece.y += CELL_SIZE;
                }

                lockPiece(activePiece, gameGrid);
                activePiece = spawnRandomPiece();
                if (checkCollision(activePiece.x, activePiece.y, activePiece, gameGrid)) {
                    return 2; // Game over
                }
            }
        }
    }

    return 0;
}

Piece spawnRandomPiece() {
    // Take random number and make it 0-6
    int pieceNum = rand() % 7;

    switch(pieceNum) {
        case 0: return createOPiece();
        case 1: return createIPiece();
        case 2: return createJPiece();
        case 3: return createLPiece();
        case 4: return createSPiece();
        case 5: return createZPiece();
        case 6: return createTPiece();
    }

    return createOPiece();
}
