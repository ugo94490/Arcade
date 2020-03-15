/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML()
{
    window.create(sf::VideoMode(1280, 720), "Arcade", sf::Style::Close);
}

LibSFML::~LibSFML()
{
    window.close();
}

void LibSFML::loadGame(const std::string &gamename)
{
    std::string spritesheetname = "games/" + gamename + "/spritesheet.png";

    texture.loadFromFile(spritesheetname.c_str());
    sprite.setTexture(texture);
}

char LibSFML::getEvent()
{
    if (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return (-2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return (-2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) return (-1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return (1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return (2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return (3);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return (4);
        }
    }
    return (0);
}

void LibSFML::draw(std::shared_ptr<IGame> game)
{
    std::list<std::shared_ptr<IGameObject>> objects = game->getObjects();
    Rect rect;
    sf::IntRect intrect;

    window.clear(sf::Color::Black);
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        rect = game->getAppearanceRectIdx(it->get()->getAppearance());
        intrect = {rect.left, rect.top, rect.width, rect.height};
        sprite.setTextureRect(intrect);
        sprite.setPosition(sf::Vector2f(it->get()->getPos().first, it->get()->getPos().second));
        window.draw(sprite);
    }
    window.display();
}