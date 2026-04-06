#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "board/Board.h"

class Renderer {
public:
    Renderer();
    void loadTextures();
    void drawBoard(sf::RenderWindow& window, const Board& board, bool pieceSelected, Position selectedPos);
    void drawPieces(sf::RenderWindow& window, const Board& board);

private:
    static const int TILE = 80;
    sf::Color lightColor{240, 217, 181};
    sf::Color darkColor{181, 136, 99};
    sf::Color highlightColor{186, 202, 68};

    std::map<std::string, sf::Texture> textures;
    std::string getTextureKey(PieceType type, PieceColor color) const;
};