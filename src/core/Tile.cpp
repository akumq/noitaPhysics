#include "core/Tile.hpp"

Tile::Tile(int x, int y) : position(x, y) {}

Tile::Tile(sf::Vector2f position) : position(position) {}

void Tile::setPos(sf::Vector2f newPosition) {
    if(!pinned){
        sf::Vector2f oldPosition = sf::Vector2f(position.x, position.y);
        position = sf::Vector2f(newPosition);
        if (oldPosition != newPosition) {
            hasChanged = true;
        }
    }
}

void Tile::setPos(float x, float y) {
    setPos(sf::Vector2f(x, y));
}

void Tile::update() {
    if (!pinned) {
        sf::Vector2f newPosition = position;
        newPosition.y += 1; // Move down one cell
        setPos(newPosition);
    }
}

sf::RectangleShape Tile::getShape() {
    sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
    rect.setPosition(position * Config::CELL_SIZE);
    rect.setFillColor(sf::Color::White);
    return rect;
}

bool Tile::checkWorldBound(const sf::Vector2f& pos){
    if (pos.x < 0 || pos.x >= Config::WIDTH / Config::CELL_SIZE ||
        pos.y < 0 || pos.y >= Config::HEIGHT / Config::CELL_SIZE) {
        return false;
    }
    return true;
}

void Tile::swapPositions(Tile* other) {
    sf::Vector2f temp = position;
    position = other->position;
    other->position = temp;
    hasChanged = true;
    other->hasChanged = true;
}