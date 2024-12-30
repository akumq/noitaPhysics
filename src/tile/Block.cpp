#include "tile/Block.hpp"
#include "config/Config.hpp"

Block::Block(int x, int y) : Tile(x, y) {
    pinned = true;
}

Block::Block(sf::Vector2f position) : Tile(position) {
    pinned = true;
}

void Block::update() {
    // Les blocs ne se déplacent pas, donc la méthode update ne fait rien
}

sf::RectangleShape Block::getShape() {
    sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
    rect.setPosition(position * Config::CELL_SIZE);
    rect.setFillColor(sf::Color(120,120,120,255)); // Couleur du bloc
    return rect;
}
