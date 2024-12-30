#ifndef TILE_SELECTOR_H
#define TILE_SELECTOR_H

#include <SFML/Graphics.hpp>
#include "config/TileHandler.hpp"
#include "core/Tile.hpp"
#include <vector>

class TileSelector {
public:
    TileSelector();
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event event, sf::RenderWindow& window);
    TileHandler::TileType getSelectedTileType() const;

private:
    TileHandler::TileType selectedTileType;
    sf::Font font;
    sf::Text text;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::RectangleShape> tileShapes;
    void updateTileShapes();
};

#endif // TILE_SELECTOR_H
