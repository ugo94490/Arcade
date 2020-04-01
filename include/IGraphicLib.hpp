/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** IGraphicLib
*/

#pragma once

#include <string>
#include <list>
#include <memory>
#include "IGame.hpp"

class IGraphicLib {
    public:
        virtual ~IGraphicLib() = default;
        virtual char getEvent() = 0;
        virtual void draw(std::shared_ptr<IGame> game) = 0;
        virtual void loadGame(const std::string &gamename) = 0;
        virtual void draw_score(int score, std::pair<float, float> pos) = 0;
        virtual void gameOver(int score) = 0;
};
