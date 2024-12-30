#ifndef BLOCK_H
#define BLOCK_H

#include "core/Tile.hpp"

class Block : public Tile {
public:
    Block(int x, int y);
    Block(sf::Vector2f position);

    void update() override;
    sf::RectangleShape getShape() override;
};

#endif // BLOCK_H
