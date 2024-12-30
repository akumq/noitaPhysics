#ifndef TILE_HANDLER_H
#define TILE_HANDLER_H

#include "core/Tile.hpp"
#include "tile/Sand.hpp"
#include "tile/Block.hpp"

class World;

class TileHandler {
public:
    static int constexpr TileTypes = 2;

    enum TileType {
        SAND = 0,
        BLOCK = 1,
    };

    static Tile* SwitchTile(sf::Vector2f position, int Type, World* world);
};

#endif // TILE_HANDLER_H
