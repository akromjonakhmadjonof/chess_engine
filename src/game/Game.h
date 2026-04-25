#pragma once
#include <SFML/Graphics.hpp>
#include "board/Board.h"
#include "renderer/Renderer.h"

class Game {
public:
    Game();

    void run();

private:
    void handleInput();

    void render();

    void updateGameStateAfterMove();

    void doAIMove();

    sf::RenderWindow window;
    Board board;
    Renderer renderer;

    bool whiteTurn = true;
    bool gameOver = false;
    bool pieceSelected = false;
    Position selectedPos = {-1, -1};

    static const int TILE = 80;
};
