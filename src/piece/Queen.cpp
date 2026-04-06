#include "piece/Queen.h"
#include "piece/Rook.h"
#include "piece/Bishop.h"

bool Queen::isValidMove(const Board& board, Position from, Position to, PieceColor color) {
    // Queen = Rook + Bishop
    return Rook::isValidMove(board, from, to, color) ||
           Bishop::isValidMove(board, from, to, color);
}