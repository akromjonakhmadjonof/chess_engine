#include "piece/Rook.h"

bool Rook::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    if (from.row != to.row && from.col != to.col) return false;
    if (from.row == to.row && from.col == to.col) return false;

    int rowStep = 0, colStep = 0;
    if (to.row > from.row) rowStep = 1;
    else if (to.row < from.row) rowStep = -1;
    if (to.col > from.col) colStep = 1;
    else if (to.col < from.col) colStep = -1;

    int r = from.row + rowStep;
    int c = from.col + colStep;
    while (r != to.row || c != to.col) {
        if (!board.getPiece(r, c).isEmpty()) return false;
        r += rowStep;
        c += colStep;
    }

    Piece target = board.getPiece(to.row, to.col);
    return target.isEmpty() || target.color != color;
}