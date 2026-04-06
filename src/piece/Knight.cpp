#include "piece/Knight.h"
#include <cmath>

bool Knight::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    int rowDiff = abs(to.row - from.row);
    int colDiff = abs(to.col - from.col);

    // L-shape: 2+1 or 1+2
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        Piece target = board.getPiece(to.row, to.col);
        if (target.isEmpty() || target.color != color) {
            return true;
        }
    }

    return false;
}