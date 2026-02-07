#include "constants.h"
#include "pieces.h"
#include <vector>

// Create all pieces in a vector to place on gameGrid
Piece createOPiece() {
    Piece O;
    O.shape = {{1,1}, {1,1}};
    O.r = 255;
    O.g = 255;
    O.b = 0;

    return O;
}

Piece createIPiece() {
    Piece I;
    I.shape = {{0,0,0,0}, {2,2,2,2}, {0,0,0,0}, {0,0,0,0}};
    I.r = 0;
    I.g = 255;
    I.b = 255;

    return I;
}

Piece createTPiece() { 
    Piece T;
    T.shape = {{0,3,0}, {3,3,3}, {0,0,0}};
    T.r = 128;
    T.g = 0;
    T.b = 128;

    return T;
}

Piece createLPiece() {
    Piece L;
    L.shape = {{0,4,0}, {0,4,0}, {0,4,4}};
    L.r = 255;
    L.g = 165;
    L.b = 0;

    return L;
}

Piece createJPiece() {
    Piece J;
    J.shape = {{0,5,0}, {0,5,0}, {5,5,0}};
    J.r = 0;
    J.g = 0;
    J.b = 255;

    return J;
}

Piece createSPiece() {
    Piece S;
    S.shape = {{0,6,6}, {6,6,0}, {0,0,0}};
    S.r = 0;
    S.g = 255;
    S.b = 0;

    return S;
}
Piece createZPiece() {
    Piece Z;
    Z.shape = {{7,7,0}, {0,7,7}, {0,0,0}};
    Z.r = 255;
    Z.g = 0;
    Z.b = 0;

    return Z;
}