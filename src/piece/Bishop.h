#pragma once
#include "board/Board.h"

class Bishop {
public:
    static bool isValidMove(const Board& board, Position from, Position to, PieceColor color);
};