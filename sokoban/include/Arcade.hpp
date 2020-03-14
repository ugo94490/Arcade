/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#pragma once

#include <ctime>
#include "Sokoban.hpp"
#include "LibSFML.hpp"
#include "LibNcurses.hpp"

class Arcade {
    public:
        Arcade(const std::string &baselib);
        ~Arcade();
        int loop();
        void switchlib();

    protected:
    private:
        Sokoban game;
        std::shared_ptr<IGraphicLib> lib;
        std::list<std::shared_ptr<IGameObject>> objects;
        std::string libname;
};
