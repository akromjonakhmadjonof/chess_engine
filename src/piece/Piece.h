#pragma once

enum class PieceType {
    None, Pawn, Knight, Bishop, Rook, Queen, King
};

enum class PieceColor {
    None, White, Black
};

struct Position;

class Piece {
public:
    PieceType type;
    PieceColor color;

    Piece();
    Piece(PieceType type, PieceColor color);

    bool isEmpty() const;
    bool isWhite() const;
    bool isBlack() const;
};