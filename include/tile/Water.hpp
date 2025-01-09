#ifndef WATER_H
#define WATER_H

#include "core/Tile.hpp"

class World;

class Water : public Tile {
public:
    const float FluidMass =  Config::WATER_MASS;

    Water(int x, int y, World* world);
    Water(sf::Vector2f position, World* world);

    void update() override;
    sf::RectangleShape getShape() override;

private:
    World* world;

    bool checkCollision(const sf::Vector2f& pos);
};

#endif // WATER_H
