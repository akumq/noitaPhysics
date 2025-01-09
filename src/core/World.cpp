#include "core/World.hpp"
#include "config/TileHandler.hpp"

World::World() {}

void World::reset() {
    tileMap.clear();
}

void World::addTile(sf::Vector2f position, int type) {
    position = toGridPosition(position);

    Tile* tile = TileHandler::SwitchTile(position, type, this);
    // std::cout << "\n Position x: \t" << position.x << "\n Position y: \t" << position.y << std::endl;
    tileMap[position] = tile;
}

void World::addTilesInRadius(sf::Vector2f center, float radius, int type) {
    sf::Vector2f start = center - sf::Vector2f(radius, radius);
    sf::Vector2f end = center + sf::Vector2f(radius, radius);

    for (int y = start.y; y <= end.y; ++y) {
        for (int x = start.x; x <= end.x; ++x) {
            sf::Vector2f position(x, y);
            if (std::abs(position.x - center.x) + std::abs(position.y - center.y) <= radius) {
                addTile(position, type);
            }
        }
    }
}

std::vector<sf::Vector2f> World::getNeighbors(const sf::Vector2f& position) const {
    std::vector<sf::Vector2f> neighbors;
    neighbors.push_back(position + sf::Vector2f(-1, -1)); // Top-left
    neighbors.push_back(position + sf::Vector2f(0, -1));  // Top
    neighbors.push_back(position + sf::Vector2f(1, -1)); // Top-right
    neighbors.push_back(position + sf::Vector2f(-1, 0));  // Left
    neighbors.push_back(position + sf::Vector2f(1, 0));   // Right
    neighbors.push_back(position + sf::Vector2f(-1, 1)); // Bottom-left
    neighbors.push_back(position + sf::Vector2f(0, 1));   // Bottom
    neighbors.push_back(position + sf::Vector2f(1, 1));   // Bottom-right
    return neighbors;
}

Tile* World::getGridTile(const sf::Vector2f position) {
    auto it = tileMap.find(position);
    if (it != tileMap.end()) {
        return it->second;
    }
    return nullptr;
}

void World::update() {
    if (clock.getElapsedTime().asSeconds() >= Config::TIME_STEP) {
        std::vector<Tile*> tilesToUpdate;

        // Collect tiles to update
        for (auto& pair : tileMap) {
            tilesToUpdate.push_back(pair.second);
        }

        // Update from bottom to top
        std::sort(tilesToUpdate.begin(), tilesToUpdate.end(),
            [](Tile* a, Tile* b) { return a->position.y > b->position.y; });

        // Stocker les positions précédentes pour gérer les swaps
        std::map<Tile*, sf::Vector2f> oldPositions;
        for (Tile* tile : tilesToUpdate) {
            oldPositions[tile] = tile->position;
        }

        for (Tile* tile : tilesToUpdate) {
            sf::Vector2f oldPos = oldPositions[tile];
            tile->update();

            // Check collision with the ground
            if (tile->position.y >= Config::HEIGHT / Config::CELL_SIZE) {
                tile->setPos(oldPos);
                continue;
            }

            // Si la position a changé, mettre à jour la map
            if (tile->hasChanged) {
                // Supprimer l'ancienne entrée
                tileMap.erase(oldPos);
                
                // Si un autre tile était à la nouvelle position (cas du swap)
                auto existingTile = tileMap.find(tile->position);
                if (existingTile != tileMap.end() && existingTile->second != tile) {
                    // L'autre tile a déjà été mis à jour à l'ancienne position de celui-ci
                    tileMap[oldPos] = existingTile->second;
                }
                
                // Mettre à jour la nouvelle position
                tileMap[tile->position] = tile;
                tile->hasChanged = false;
            }
        }

        clock.restart();
    }
}

void World::updateTilePosition(Tile* tile, const sf::Vector2f& oldPos, const sf::Vector2f& newPos) {
    tileMap.erase(oldPos);
    tileMap[newPos] = tile;
}

void World::draw(sf::RenderWindow& window) {
    for (auto& pair : tileMap) {
        Tile* tile = pair.second;
        window.draw(tile->getShape());
    }
}

sf::Vector2f World::toGridPosition(sf::Vector2f position) {
    return sf::Vector2f(std::trunc(position.x / Config::CELL_SIZE), std::trunc(position.y / Config::CELL_SIZE));
}

bool World::VectorComparator::operator() (sf::Vector2f lhs, sf::Vector2f rhs) const {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}
