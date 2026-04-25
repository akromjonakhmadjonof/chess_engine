#include "game/Game.h"
#include "ai/AI.h"

Game::Game()
    : window(sf::VideoMode({640, 640}), "Chess") {
    window.setTitle("Chess - White to move");
}

void Game::run() {
    while (window.isOpen()) {
        handleInput();

        if (!gameOver && !whiteTurn) {
            doAIMove();
        }

        render();
    }
}

void Game::doAIMove() {
    auto move = AI::getBestMove(board, PieceColor::Black, 3);
    if (move.has_value()) {
        board.movePiece(move->from, move->to);
        whiteTurn = true;
        updateGameStateAfterMove();
    }
}

void Game::handleInput() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (gameOver || !whiteTurn) continue;

        if (auto *mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                int col = mouseEvent->position.x / TILE;
                int row = mouseEvent->position.y / TILE;

                if (!board.isInBounds(row, col)) continue;

                if (!pieceSelected) {
                    Piece piece = board.getPiece(row, col);
                    if (!piece.isEmpty() && piece.isWhite()) {
                        pieceSelected = true;
                        selectedPos = {row, col};
                    }
                } else {
                    if (row == selectedPos.row && col == selectedPos.col) {
                        pieceSelected = false;
                    } else {
                        Piece target = board.getPiece(row, col);
                        bool ownPiece = target.isWhite();

                        if (ownPiece) {
                            selectedPos = {row, col};
                        } else {
                            Position targetPos = {row, col};
                            if (board.isValidMove(selectedPos, targetPos)) {
                                board.movePiece(selectedPos, targetPos);
                                pieceSelected = false;
                                whiteTurn = false;
                                updateGameStateAfterMove();
                            } else {
                                pieceSelected = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::updateGameStateAfterMove() {
    PieceColor sideToMove = whiteTurn ? PieceColor::White : PieceColor::Black;

    if (board.isCheckmate(sideToMove)) {
        gameOver = true;
        PieceColor winner = whiteTurn ? PieceColor::Black : PieceColor::White;
        window.setTitle((winner == PieceColor::White)
                            ? "Chess - Checkmate! White wins"
                            : "Chess - Checkmate! Black wins");
        return;
    }

    if (board.isStalemate(sideToMove)) {
        gameOver = true;
        window.setTitle("Chess - Stalemate");
        return;
    }

    if (board.isKingInCheck(sideToMove)) {
        window.setTitle(whiteTurn ? "Chess - White in check" : "Chess - Black in check");
    } else {
        window.setTitle(whiteTurn ? "Chess - White to move" : "Chess - Black to move");
    }
}

void Game::render() {
    window.clear();
    renderer.drawBoard(window, board, pieceSelected, selectedPos);
    renderer.drawPieces(window, board);
    window.display();
}
