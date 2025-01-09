#include "config/TileHandler.hpp"
#include "core/World.hpp"

Tile* TileHandler::SwitchTile(sf::Vector2f position, int Type, World* world) {
    Tile* tile;
    switch (Type) {
        case SAND:
            tile = new Sand(position, world);
            break;
        case BLOCK:
            tile = new Block(position);
            break;
        case WATER:
            tile = new Water(position,world);
            break;
        case ACID:
            tile = new Acid(position,world);
            break;
        default:
            tile = new Tile(position);
            break;
    }
    return tile;
}
