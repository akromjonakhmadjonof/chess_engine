#pragma once
#include "board/Board.h"
#include <optional>

struct Move {
    Position from;
    Position to;
};

class AI {
public:
    static std::optional<Move> getBestMove(const Board& board, PieceColor color, int depth);

private:
    static int minimax(Board board, int depth, int alpha, int beta, bool maximizing, PieceColor aiColor);
    static int evaluate(const Board& board, PieceColor aiColor);
    static int pieceValue(PieceType type);
};