#include "core/InputHandler.hpp"

bool InputHandler::mouse_pressed = false;
float InputHandler::radius = Config::MOUSE_RADIUS_BASE;
TileHandler::TileType InputHandler::selectedTileType = TileHandler::SAND;

void InputHandler::handle_mouse_click(sf::Event event, sf::RenderWindow& window, World& world, TileSelector& tileSelector) {
    tileSelector.handleEvent(event, window);
    selectedTileType = tileSelector.getSelectedTileType();

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                radius += Config::MOUSE_RADIUS_STEP;
                radius = std::min(radius, Config::MOUSE_RADIUS_MAX);
                break;
            case sf::Keyboard::Down:
                radius -= Config::MOUSE_RADIUS_STEP;
                radius = std::max(radius, Config::MOUSE_RADIUS_MIN);
                break;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        mouse_pressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        mouse_pressed = false;
    }

    if (mouse_pressed) {
        sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        world.addTilesInRadius(mouse_pos, radius, selectedTileType);
    }
}

void InputHandler::draw_radius(sf::RenderWindow& window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::CircleShape circle(radius);
    circle.setPosition(mouse_pos.x - radius, mouse_pos.y - radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.0f);
    window.draw(circle);
}