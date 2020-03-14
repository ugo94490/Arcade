/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSFML
*/

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "IGraphicLib.hpp"
#include "print_appearance.hpp"

class LibSFML : public IGraphicLib {
    public:
        LibSFML(const std::string &name = "Arcade");
        ~LibSFML();
        char getEvent();
        void draw(std::list<std::shared_ptr<IGameObject>> objects);

    protected:
        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite sprite;
    private:
};
