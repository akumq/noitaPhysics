#include "tile/Water.hpp"
#include "core/World.hpp"

Water::Water(int x, int y, World* world) : Tile(x, y), world(world) {
    isFluid = true;
}

Water::Water(sf::Vector2f position, World* world) : Tile(position), world(world){
    isFluid = true;
}

void Water::update() {
    if (!pinned) {
        sf::Vector2f oldPosition = position;
        sf::Vector2f newPosition = position;

        const std::vector<sf::Vector2f> moves = {
            sf::Vector2f(0, 1),    // bottom
            sf::Vector2f(-1, 1),   // bottom-left
            sf::Vector2f(1, 1),    // bottom-right
            sf::Vector2f(-1, 0),   // left
            sf::Vector2f(1, 0)     // right
        };

        for (const auto& move : moves) {
            newPosition = position + move;
            
            if (!checkWorldBound(newPosition)) {
                continue;
            }

            Tile* otherTile = world->getGridTile(newPosition);
            
            if (otherTile == nullptr) {
                // Case vide - déplacement simple
                position = newPosition;
                hasChanged = true;
                world->tileMap.erase(oldPosition);
                world->tileMap[newPosition] = this;
                return;
            } 
           
        }
    }
}
sf::RectangleShape Water::getShape() {
    sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
    rect.setPosition(position * Config::CELL_SIZE);
    rect.setFillColor(sf::Color(10, 10, 255,255));
    return rect;
}

bool Water::checkCollision(const sf::Vector2f& pos) {
    if (!checkWorldBound(pos)) {
        return true;
    }
    Tile* tile = world->getGridTile(pos);
    if (tile == nullptr) {
        return false;
    }
    if (tile->isFluid && tile != this && tile->FluidMass < FluidMass) {
        return false;
    }
    return true;
}
