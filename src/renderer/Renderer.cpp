#include "renderer/Renderer.h"

Renderer::Renderer() {
    loadTextures();
}

void Renderer::loadTextures() {
    std::map<std::string, std::string> files = {
        {"wP", "assets/wP.png"}, {"wN", "assets/wN.png"}, {"wB", "assets/wB.png"},
        {"wR", "assets/wR.png"}, {"wQ", "assets/wQ.png"}, {"wK", "assets/wK.png"},
        {"bP", "assets/bP.png"}, {"bN", "assets/bN.png"}, {"bB", "assets/bB.png"},
        {"bR", "assets/bR.png"}, {"bQ", "assets/bQ.png"}, {"bK", "assets/bK.png"}
    };

    for (auto &[key, file]: files) {
        sf::Texture tex(file);
        tex.setSmooth(true);
        textures[key] = std::move(tex);
    }
}

std::string Renderer::getTextureKey(PieceType type, PieceColor color) const {
    std::string key = (color == PieceColor::White) ? "w" : "b";
    switch (type) {
        case PieceType::Pawn: key += "P";
            break;
        case PieceType::Knight: key += "N";
            break;
        case PieceType::Bishop: key += "B";
            break;
        case PieceType::Rook: key += "R";
            break;
        case PieceType::Queen: key += "Q";
            break;
        case PieceType::King: key += "K";
            break;
        default: return "";
    }
    return key;
}

void Renderer::drawBoard(sf::RenderWindow &window, const Board &board, bool pieceSelected, Position selectedPos) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape square(sf::Vector2f(TILE, TILE));
            square.setPosition(sf::Vector2f(col * TILE, row * TILE));

            if (pieceSelected && row == selectedPos.row && col == selectedPos.col)
                square.setFillColor(highlightColor);
            else if ((row + col) % 2 == 0)
                square.setFillColor(lightColor);
            else
                square.setFillColor(darkColor);

            window.draw(square);
        }
    }
}

void Renderer::drawPieces(sf::RenderWindow &window, const Board &board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = board.getPiece(row, col);
            if (!piece.isEmpty()) {
                std::string key = getTextureKey(piece.type, piece.color);
                if (!key.empty() && textures.count(key)) {
                    sf::Sprite sprite(textures[key]);
                    auto size = textures[key].getSize();
                    sprite.setScale(sf::Vector2f(
                        (float) TILE / size.x,
                        (float) TILE / size.y
                    ));
                    sprite.setPosition(sf::Vector2f(col * TILE, row * TILE));
                    window.draw(sprite);
                }
            }
        }
    }
}
