#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/World.hpp"
#include "core/InputHandler.hpp"
#include "config/Config.hpp"
#include "menu/TileSelector.hpp"

void init_simulation(World& world) {
    world.reset();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Config::WIDTH, Config::HEIGHT), "SFML Project");
    World world;
    TileSelector tileSelector;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                init_simulation(world);
            InputHandler::handle_mouse_click(event, window, world, tileSelector);
        }

        window.clear(sf::Color(0, 0, 0, 0));

        world.draw(window);
        world.update();
        
        tileSelector.draw(window);
        window.display();
    }

    return 0;
}
