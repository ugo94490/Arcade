/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** LibNcurses
*/

#pragma once

#include <ncurses.h>
#include "IGraphicLib.hpp"
#include "print_appearance.hpp"

class LibNcurses : public IGraphicLib {
    public:
        LibNcurses();
        ~LibNcurses();
        char getEvent();
        void draw(std::list<std::shared_ptr<IGameObject>> objects);

    protected:
        WINDOW *window;
    private:
};
