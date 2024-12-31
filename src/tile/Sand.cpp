#include "tile/Sand.hpp"
#include "core/World.hpp"

#include <cstdlib>



Sand::Sand(int x, int y, World* world) : Tile(x, y), world(world) {}

Sand::Sand(sf::Vector2f position, World* world) : Tile(position), world(world) {}

void Sand::update() {
    std::srand(time(0));
    if (!pinned) {
        sf::Vector2f newPosition = position;

        // Check bottom
        newPosition.y += 1;
        if (checkWorldBound(newPosition)) {
            Tile* tile = world->getGridTile(newPosition);
            if (tile == nullptr) {
                setPos(newPosition);
                return;
            } else if (tile->isFluid) {
                swapPositions(tile);
                return;
            }
        }

        // Check bottom-left
        newPosition = position + sf::Vector2f(-1, 1);
        if (checkWorldBound(newPosition)) {
            Tile* tile = world->getGridTile(newPosition);
            if (tile == nullptr) {
                setPos(newPosition);
                return;
            } else if (tile->isFluid) {
                swapPositions(tile);
                return;
            }
        }

        // Check bottom-right
        newPosition = position + sf::Vector2f(1, 1);
        if (checkWorldBound(newPosition)) {
            Tile* tile = world->getGridTile(newPosition);
            if (tile == nullptr) {
                setPos(newPosition);
                return;
            } else if (tile->isFluid) {
                swapPositions(tile);
                return;
            }
        }
    }
}

sf::RectangleShape Sand::getShape() {
    sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
    rect.setPosition(position * Config::CELL_SIZE);
    rect.setFillColor(sf::Color(194, 178, 128));
    return rect;
}

bool Sand::checkCollision(const sf::Vector2f& pos) {
    if (!checkWorldBound(pos)) {
        return true;
    }
    Tile* tile = world->getGridTile(pos);
    return tile != nullptr;
}