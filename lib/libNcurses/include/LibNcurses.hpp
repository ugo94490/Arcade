/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** LibNcurses
*/

#pragma once

#include <ncurses.h>
#include "IGraphicLib.hpp"

class LibNcurses : public IGraphicLib {
    public:
        LibNcurses();
        ~LibNcurses();
        char getEvent();
        void draw(std::shared_ptr<IGame> game);
        void loadGame(const std::string &path);

    protected:
        WINDOW *window;
    private:
};

extern "C" {
    IGraphicLib *maker() {
        return new LibNcurses();
    }
}