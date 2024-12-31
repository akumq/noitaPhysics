#ifndef ACID_H
#define ACID_H

#include "core/Tile.hpp"

class World;

class Acid : public Tile {
public:
    Acid(int x, int y, World* world);
    Acid(sf::Vector2f position, World* world);

    void update() override;
    sf::RectangleShape getShape() override;

private:
    World* world;

    bool checkCollision(const sf::Vector2f& pos);
};

#endif // ACID_H
