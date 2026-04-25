#pragma once
#include "board/Board.h"

class King {
public:
    static bool isValidMove(const Board& board, Position from, Position to, PieceColor color);
};