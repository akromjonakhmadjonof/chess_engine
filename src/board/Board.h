#pragma once
#include "piece/Piece.h"

struct Position {
    int row;
    int col;
};

class Board {
public:
    Board();
    void init();
    Piece getPiece(int row, int col) const;
    void movePiece(Position from, Position to);
    bool isInBounds(int row, int col) const;
    bool isValidMove(Position from, Position to);

private:
    Piece grid[8][8];
};