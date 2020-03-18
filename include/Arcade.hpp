/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#pragma once

#include <ctime>
#include <dlfcn.h>
#include "IGame.hpp"
#include "IGraphicLib.hpp"

class Arcade {
    public:
        Arcade(const std::string &baselib);
        ~Arcade();
        int loop();
        void loadlib(const std::string &lib);
        void loadgame(const std::string &game);
        void switchgame();
        void switchlib();

    protected:
    private:
        std::shared_ptr<IGame> game;
        std::shared_ptr<IGraphicLib> lib;
        std::list<std::shared_ptr<IGameObject>> objects;
        std::string libname;
        std::string gamename;
};
