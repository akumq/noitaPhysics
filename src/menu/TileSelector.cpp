#include "menu/TileSelector.hpp"
#include <iostream>
#include "config/Config.hpp"

TileSelector::TileSelector() : selectedTileType(TileHandler::SAND) {
    // Initialiser les boutons et les formes de tuiles
    updateTileShapes();
}

void TileSelector::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        // window.draw(buttons[i]);
        window.draw(tileShapes[i]);
    }
}

void TileSelector::handleEvent(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos)) {
                selectedTileType = static_cast<TileHandler::TileType>(i);
                std::cout << selectedTileType << std::endl;
                break;
            }
        }
    }
}

TileHandler::TileType TileSelector::getSelectedTileType() const {
    return selectedTileType;
}

void TileSelector::updateTileShapes() {
    buttons.clear();
    tileShapes.clear();

    float buttonWidth = Config::WIDTH / (TileHandler::BLOCK + 1); // Largeur des boutons
    float buttonHeight = 50; // Hauteur des boutons
    
    for (int i = 0; i <= TileHandler::TileTypes; ++i) {
        Tile* tile = TileHandler::SwitchTile(sf::Vector2f(0, 0), i, nullptr);
        sf::RectangleShape tileShape = tile->getShape();
        tileShape.setSize(sf::Vector2f(buttonWidth - 10, buttonHeight - 10)); // Ajuster la taille pour l'affichage
        tileShape.setPosition(i * buttonWidth + 5, 5); // Positionner la forme de la tuile
        tileShapes.push_back(tileShape);

        sf::RectangleShape button;
        button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(i * buttonWidth, 0);
        button.setFillColor(sf::Color::Blue);
        buttons.push_back(button);

        delete tile; // Supprimer la tuile temporaire
    }
}
