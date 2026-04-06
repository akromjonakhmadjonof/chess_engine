#include "board/Board.h"
#include "piece/Pawn.h"
#include "piece/Knight.h"
#include "piece/Bishop.h"
#include "piece/Rook.h"
#include "piece/Queen.h"
#include "piece/King.h"

Board::Board() {
    init();
}

void Board::init() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            grid[r][c] = Piece();

    PieceType backRank[] = {
        PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen,
        PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook
    };

    for (int c = 0; c < 8; c++) {
        grid[0][c] = Piece(backRank[c], PieceColor::Black);
        grid[1][c] = Piece(PieceType::Pawn, PieceColor::Black);
        grid[6][c] = Piece(PieceType::Pawn, PieceColor::White);
        grid[7][c] = Piece(backRank[c], PieceColor::White);
    }
}

Piece Board::getPiece(int row, int col) const {
    if (!isInBounds(row, col))
        return Piece();
    return grid[row][col];
}

void Board::movePiece(Position from, Position to) {
    if (!isInBounds(from.row, from.col) || !isInBounds(to.row, to.col))
        return;
    grid[to.row][to.col] = grid[from.row][from.col];
    grid[from.row][from.col] = Piece();
}

bool Board::isInBounds(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool Board::isValidMove(Position from, Position to) {
    if (!isInBounds(from.row, from.col) || !isInBounds(to.row, to.col))
        return false;

    Piece piece = getPiece(from.row, from.col);
    if (piece.isEmpty()) return false;

    switch (piece.type) {
        case PieceType::Pawn:   return Pawn::isValidMove(*this, from, to, piece.color);
        case PieceType::Knight: return Knight::isValidMove(*this, from, to, piece.color);
        case PieceType::Bishop: return Bishop::isValidMove(*this, from, to, piece.color);
        case PieceType::Rook:   return Rook::isValidMove(*this, from, to, piece.color);
        case PieceType::Queen:  return Queen::isValidMove(*this, from, to, piece.color);
        case PieceType::King:   return King::isValidMove(*this, from, to, piece.color);
        default: return false;
    }
}