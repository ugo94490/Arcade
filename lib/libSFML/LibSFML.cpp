/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSFML
*/

#include "LibSFML.hpp"

LibSFML::LibSFML()
{
    window.create(sf::VideoMode(1280, 720), "Arcade SFML", sf::Style::Close);
}

LibSFML::~LibSFML()
{
    window.close();
}

void LibSFML::loadGame(const std::string &gamename)
{
    std::string spritesheetname = "games/" + gamename + "/spritesheet.png";

    window.setTitle(gamename + " SFML");
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
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) return (-5);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) return (-4);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) return (-3);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return (-2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) return (-1);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return (1);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return (2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return (3);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return (4);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return (5);
            }
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
        sprite.setScale(0.5, 0.5);
        window.draw(sprite);
    }
    window.display();
}

void LibSFML::init_score(int score, std::pair<float, float> pos)
{
    sf::Vector2f pos_txt = {(float) pos.first, (float) pos.second};

    font.loadFromFile("lib/libSFML/SNES.ttf");
    text.setFont(font);
    text.setCharacterSize(55);
    text.setPosition(pos_txt);
}

void LibSFML::draw_score(int score, std::pair<float, float> pos)
{
    std::string str = "Score " + std::to_string(score);
    sf::Vector2f pos_txt = {(float) pos.first, (float) pos.second};

    text.setPosition(pos_txt);
    text.setString(str);
    window.draw(text);
    window.display();
}

void LibSFML::gameOver(int score)
{
    static clock_t timer = clock();
    sf::Text text;
    sf::Font font;
    std::pair<float, float> posScore = std::pair<float, float>(535, 300);
    sf::Vector2f pos_txt = {(float) 400, (float) 150};
    std::string str = "GAME OVER";

    font.loadFromFile("lib/libSFML/SNES.ttf");
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(155);
    text.setPosition(pos_txt);
    window.clear(sf::Color::Black);
    draw_score(score, posScore);
    window.draw(text);
    window.display();
    while (clock() - timer <= 6000000) {
    }
}