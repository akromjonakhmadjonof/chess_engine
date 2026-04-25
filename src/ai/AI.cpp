#include "ai/AI.h"
#include <limits>
#include <algorithm>

int AI::pieceValue(PieceType type) {
    switch (type) {
        case PieceType::Pawn:   return 100;
        case PieceType::Knight: return 320;
        case PieceType::Bishop: return 330;
        case PieceType::Rook:   return 500;
        case PieceType::Queen:  return 900;
        case PieceType::King:   return 20000;
        default:                return 0;
    }
}

int AI::evaluate(const Board& board, PieceColor aiColor) {
    int score = 0;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = board.getPiece(r, c);
            if (p.isEmpty()) continue;
            int val = pieceValue(p.type);
            score += (p.color == aiColor) ? val : -val;
        }
    }
    return score;
}

int AI::minimax(Board board, int depth, int alpha, int beta, bool maximizing, PieceColor aiColor) {
    PieceColor humanColor = (aiColor == PieceColor::White) ? PieceColor::Black : PieceColor::White;
    PieceColor sideToMove = maximizing ? aiColor : humanColor;

    if (board.isCheckmate(sideToMove)) return maximizing ? -100000 : 100000;
    if (board.isStalemate(sideToMove)) return 0;
    if (depth == 0) return evaluate(board, aiColor);

    int best = maximizing ? std::numeric_limits<int>::min()
                          : std::numeric_limits<int>::max();
    bool pruned = false;

    for (int fr = 0; fr < 8 && !pruned; fr++) {
        for (int fc = 0; fc < 8 && !pruned; fc++) {
            Piece piece = board.getPiece(fr, fc);
            if (piece.isEmpty() || piece.color != sideToMove) continue;

            for (int tr = 0; tr < 8 && !pruned; tr++) {
                for (int tc = 0; tc < 8 && !pruned; tc++) {
                    if (!board.isValidMove({fr, fc}, {tr, tc})) continue;

                    Board next = board;
                    next.movePiece({fr, fc}, {tr, tc});

                    int score = minimax(next, depth - 1, alpha, beta, !maximizing, aiColor);

                    if (maximizing) {
                        best  = std::max(best, score);
                        alpha = std::max(alpha, best);
                    } else {
                        best = std::min(best, score);
                        beta = std::min(beta, best);
                    }
                    if (beta <= alpha) pruned = true;
                }
            }
        }
    }
    return best;
}

std::optional<Move> AI::getBestMove(const Board& board, PieceColor color, int depth) {
    Move bestMove{{-1, -1}, {-1, -1}};
    int bestScore = std::numeric_limits<int>::min();
    int alpha     = std::numeric_limits<int>::min();
    int beta      = std::numeric_limits<int>::max();
    bool found    = false;

    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            Piece piece = board.getPiece(fr, fc);
            if (piece.isEmpty() || piece.color != color) continue;

            for (int tr = 0; tr < 8; tr++) {
                for (int tc = 0; tc < 8; tc++) {
                    if (!board.isValidMove({fr, fc}, {tr, tc})) continue;

                    Board next = board;
                    next.movePiece({fr, fc}, {tr, tc});

                    int score = minimax(next, depth - 1, alpha, beta, false, color);
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove  = {{fr, fc}, {tr, tc}};
                        found     = true;
                    }
                    alpha = std::max(alpha, score);
                }
            }
        }
    }
    return found ? std::optional<Move>{bestMove} : std::nullopt;
}