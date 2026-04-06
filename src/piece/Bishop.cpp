#include "piece/Bishop.h"
#include <cmath>

bool Bishop::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    int rowDiff = abs(to.row - from.row);
    int colDiff = abs(to.col - from.col);

    // Must move diagonally
    if (rowDiff != colDiff || rowDiff == 0) return false;

    // Check path is clear
    int rowStep = (to.row > from.row) ? 1 : -1;
    int colStep = (to.col > from.col) ? 1 : -1;

    int r = from.row + rowStep;
    int c = from.col + colStep;
    while (r != to.row && c != to.col) {
        if (!board.getPiece(r, c).isEmpty()) return false;
        r += rowStep;
        c += colStep;
    }

    Piece target = board.getPiece(to.row, to.col);
    return target.isEmpty() || target.color != color;
}