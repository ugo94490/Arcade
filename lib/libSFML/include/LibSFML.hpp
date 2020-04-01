/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSFML
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "IGraphicLib.hpp"

class LibSFML : public IGraphicLib {
    public:
        LibSFML();
        ~LibSFML();
        char getEvent();
        void draw(std::shared_ptr<IGame> game);
        void loadGame(const std::string &path);
        void draw_score(int score, std::pair<float, float> pos);
        void gameOver(int score);

    protected:
        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite sprite;
    private:
};

extern "C" {
    IGraphicLib *maker() {
        return new LibSFML();
    }
}
