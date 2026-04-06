#include "piece/Pawn.h"

bool Pawn::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    int direction = (color == PieceColor::White) ? -1 : 1;
    int startRow = (color == PieceColor::White) ? 6 : 1;

    int rowDiff = to.row - from.row;
    int colDiff = to.col - from.col;

    Piece target = board.getPiece(to.row, to.col);

    // Move forward 1 square
    if (colDiff == 0 && rowDiff == direction && target.isEmpty()) {
        return true;
    }

    // Move forward 2 squares from starting row
    if (colDiff == 0 && rowDiff == 2 * direction && from.row == startRow && target.isEmpty()) {
        // Check that middle square is also empty
        Piece middle = board.getPiece(from.row + direction, from.col);
        if (middle.isEmpty()) {
            return true;
        }
    }

    // Capture diagonally
    if ((colDiff == 1 || colDiff == -1) && rowDiff == direction) {
        if (!target.isEmpty() && target.color != color) {
            return true;
        }
    }

    return false;
}