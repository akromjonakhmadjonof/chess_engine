#include "piece/Piece.h"

Piece::Piece() : type(PieceType::None), color(PieceColor::None) {}

Piece::Piece(PieceType type, PieceColor color) : type(type), color(color) {}

bool Piece::isEmpty() const { return type == PieceType::None; }
bool Piece::isWhite() const { return color == PieceColor::White; }
bool Piece::isBlack() const { return color == PieceColor::Black; }