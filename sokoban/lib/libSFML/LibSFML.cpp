/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML(const std::string &gamename)
{
    window.create(sf::VideoMode(1280, 720), gamename, sf::Style::Close);
    texture.loadFromFile("game/sokoban_sprites.png");
    sprite.setTexture(texture);
}

LibSFML::~LibSFML()
{
    window.close();
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

void LibSFML::draw(std::list<std::shared_ptr<IGameObject>> objects)
{
    window.clear(sf::Color::Black);
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        sprite.setTextureRect(sokoRects[it->get()->getAppearance()]);
        sprite.setPosition(sf::Vector2f(it->get()->getPos().first, it->get()->getPos().second));
        window.draw(sprite);
    }
    window.display();
}