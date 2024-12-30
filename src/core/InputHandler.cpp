#include "core/InputHandler.hpp"

bool InputHandler::mouse_pressed = false;
TileHandler::TileType InputHandler::selectedTileType = TileHandler::SAND;

void InputHandler::handle_mouse_click(sf::Event event, sf::RenderWindow& window, World& world, TileSelector& tileSelector) {
    tileSelector.handleEvent(event, window);
    selectedTileType = tileSelector.getSelectedTileType();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        mouse_pressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        mouse_pressed = false;
    }

    if (mouse_pressed) {
        sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        world.addTile(mouse_pos, selectedTileType);
    }
}
