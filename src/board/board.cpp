#include "board/Board.h"
#include "piece/Pawn.h"
#include "piece/Knight.h"
#include "piece/Bishop.h"
#include "piece/Rook.h"
#include "piece/Queen.h"
#include "piece/King.h"
#include <utility>

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

bool Board::isPseudoLegalMove(Position from, Position to) const {
    if (!isInBounds(from.row, from.col) || !isInBounds(to.row, to.col))
        return false;

    Piece piece = getPiece(from.row, from.col);
    if (piece.isEmpty()) return false;

    switch (piece.type) {
        case PieceType::Pawn: return Pawn::isValidMove(*this, from, to, piece.color);
        case PieceType::Knight: return Knight::isValidMove(*this, from, to, piece.color);
        case PieceType::Bishop: return Bishop::isValidMove(*this, from, to, piece.color);
        case PieceType::Rook: return Rook::isValidMove(*this, from, to, piece.color);
        case PieceType::Queen: return Queen::isValidMove(*this, from, to, piece.color);
        case PieceType::King: return King::isValidMove(*this, from, to, piece.color);
        default: return false;
    }
}

bool Board::wouldLeaveKingInCheck(Position from, Position to) const {
    Board simulated = *this;
    simulated.movePiece(from, to);

    Piece movedPiece = getPiece(from.row, from.col);
    return simulated.isKingInCheck(movedPiece.color);
}

bool Board::isValidMove(Position from, Position to) const {
    if (!isPseudoLegalMove(from, to)) {
        return false;
    }
    return !wouldLeaveKingInCheck(from, to);
}

Position Board::findKing(PieceColor color) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = getPiece(row, col);
            if (piece.type == PieceType::King && piece.color == color) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

bool Board::isSquareUnderAttack(Position square, PieceColor byColor) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = getPiece(row, col);
            if (piece.isEmpty() || piece.color != byColor) {
                continue;
            }

            if (isPseudoLegalMove({row, col}, square)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isKingInCheck(PieceColor color) const {
    Position kingPos = findKing(color);
    if (!isInBounds(kingPos.row, kingPos.col)) {
        return false;
    }

    PieceColor enemyColor = (color == PieceColor::White) ? PieceColor::Black : PieceColor::White;
    return isSquareUnderAttack(kingPos, enemyColor);
}

bool Board::hasAnyLegalMove(PieceColor color) const {
    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Piece piece = getPiece(fromRow, fromCol);
            if (piece.isEmpty() || piece.color != color) {
                continue;
            }

            for (int toRow = 0; toRow < 8; toRow++) {
                for (int toCol = 0; toCol < 8; toCol++) {
                    if (isValidMove({fromRow, fromCol}, {toRow, toCol})) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(PieceColor color) const {
    return isKingInCheck(color) && !hasAnyLegalMove(color);
}

bool Board::isStalemate(PieceColor color) const {
    return !isKingInCheck(color) && !hasAnyLegalMove(color);
}
