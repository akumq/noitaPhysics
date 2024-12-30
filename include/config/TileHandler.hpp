#ifndef TILE_HANDLER_H
#define TILE_HANDLER_H

#include "core/Tile.hpp"

#include "tile/Sand.hpp"
#include "tile/Block.hpp"
#include "tile/Water.hpp"

class World;

class TileHandler {
public:
    static int constexpr TileTypes = 3;

    enum TileType {
        SAND = 0,
        BLOCK = 1,
        WATER = 2,
    };

    static Tile* SwitchTile(sf::Vector2f position, int Type, World* world);
};

#endif // TILE_HANDLER_H
