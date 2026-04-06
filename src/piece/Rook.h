#pragma once
#include "board/Board.h"

class Rook {
public:
    static bool isValidMove(const Board& board, Position from, Position to, PieceColor color);
};