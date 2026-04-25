#pragma once
#include "piece/Piece.h"

struct Position {
    int row;
    int col;
};

class Board {
public:
    Board();

    void init();

    Piece getPiece(int row, int col) const;

    void movePiece(Position from, Position to);

    bool isInBounds(int row, int col) const;

    bool isValidMove(Position from, Position to) const;

    bool isKingInCheck(PieceColor color) const;

    bool hasAnyLegalMove(PieceColor color) const;

    bool isCheckmate(PieceColor color) const;

    bool isStalemate(PieceColor color) const;

private:
    Piece grid[8][8];

    bool isSquareUnderAttack(Position square, PieceColor byColor) const;

    bool isPseudoLegalMove(Position from, Position to) const;

    bool wouldLeaveKingInCheck(Position from, Position to) const;

    Position findKing(PieceColor color) const;
};
