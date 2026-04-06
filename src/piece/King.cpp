#include "piece/King.h"
#include <cmath>

bool King::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    int rowDiff = abs(to.row - from.row);
    int colDiff = abs(to.col - from.col);

    // King moves 1 square in any direction
    if (rowDiff <= 1 && colDiff <= 1 && (rowDiff + colDiff > 0)) {
        Piece target = board.getPiece(to.row, to.col);
        return target.isEmpty() || target.color != color;
    }

    return false;
}