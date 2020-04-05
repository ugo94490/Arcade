/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#pragma once

#include <ctime>
#include <dlfcn.h>
#include <string>
#include <vector>
#include "IGame.hpp"
#include "IGraphicLib.hpp"

class Arcade {
    public:
        Arcade(std::string &baselib);
        ~Arcade();
        int loop();
        void loadlib(const std::string &lib);
        void loadgame(const std::string &game);
        void nextGame();
        void prevGame();
        void nextLib();
        void prevLib();
        static int help(char *av);

    protected:
    private:
        std::shared_ptr<IGame> game;
        std::shared_ptr<IGraphicLib> lib;
        std::list<std::shared_ptr<IGameObject>> objects;
        std::string libname;
        std::string gamename;
        std::string menu;
        std::vector<std::string> list_game;
        std::vector<std::string> list_lib;
        void *liblib;
        void *gamelib;
        int idx_lib;
        int idx_game;
        int idx_menu;
};