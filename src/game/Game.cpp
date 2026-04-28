#include "game/Game.h"

Game::Game()
    : window(sf::VideoMode({640, 640}), "Min Max Chess") {
}

void Game::run() {
    while (window.isOpen()) {
        handleInput();
        render();
    }
}

void Game::handleInput() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (auto *mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                int col = mouseEvent->position.x / TILE;
                int row = mouseEvent->position.y / TILE;

                if (!board.isInBounds(row, col)) continue;

                if (!pieceSelected) {
                    Piece piece = board.getPiece(row, col);
                    if (!piece.isEmpty()) {
                        bool correctTurn = (whiteTurn && piece.isWhite()) ||
                                           (!whiteTurn && piece.isBlack());
                        if (correctTurn) {
                            pieceSelected = true;
                            selectedPos = {row, col};
                        }
                    }
                } else {
                    if (row == selectedPos.row && col == selectedPos.col) {
                        pieceSelected = false;
                    } else {
                        Piece target = board.getPiece(row, col);
                        bool ownPiece = (whiteTurn && target.isWhite()) ||
                                        (!whiteTurn && target.isBlack());

                        if (ownPiece) {
                            selectedPos = {row, col};
                        } else {
                            Position targetPos = {row, col};
                            if (board.isValidMove(selectedPos, targetPos)) {
                                board.movePiece(selectedPos, targetPos);
                                pieceSelected = false;
                                whiteTurn = !whiteTurn;
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

void Game::render() {
    window.clear();
    renderer.drawBoard(window, board, pieceSelected, selectedPos);
    renderer.drawPieces(window, board);
    window.display();
}
