#include "tile/Acid.hpp"
#include "core/World.hpp"

Acid::Acid(int x, int y, World* world) : Tile(x, y), world(world) {
    isFluid = true;
}

Acid::Acid(sf::Vector2f position, World* world) : Tile(position), world(world){
    isFluid = true;
}

void Acid::update() {
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
                // Déplacement simple dans une case vide
                world->tileMap.erase(oldPosition);
                position = newPosition;
                world->tileMap[position] = this;
                hasChanged = true;
                return;
            } 
            else if (move.y == 1.0f  && otherTile != this) {
                // Vérifier si c'est du même type
                bool isSameType = typeid(*otherTile) == typeid(*this);
                if(!isSameType){
                     // Corrosion 
                    if (corrosive_count > Config::CORROSIVE_TICK){
                        corrosive_count = 0;
                        world->tileMap.erase(newPosition);
                        return;
                    }
                    else if(!hasChanged){
                        corrosive_count++;
                    }

                    if (!isSameType && otherTile->isFluid && otherTile->FluidMass < FluidMass && !otherTile->hasChanged) {
                        // Sauvegarder temporairement les positions
                        sf::Vector2f tempPos = position;
                        
                        // Retirer les deux tuiles de la map
                        world->tileMap.erase(oldPosition);
                        world->tileMap.erase(newPosition);
                        
                        // Remettre les deux tuiles dans la map avec leurs nouvelles positions
                        world->tileMap[position] = this;
                        world->tileMap[otherTile->position] = otherTile;

                        // Échanger les positions
                        position = newPosition;
                        otherTile->position = tempPos;
                        
                        hasChanged = true;
                        otherTile->hasChanged = true;
                        return;
                    }
                }
               
            }
        }
        
    }

}

sf::RectangleShape Acid::getShape() {
    sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
    rect.setPosition(position * Config::CELL_SIZE);
    rect.setFillColor(sf::Color(10, 255, 10,255));
    return rect;
}

bool Acid::checkCollision(const sf::Vector2f& pos) {
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