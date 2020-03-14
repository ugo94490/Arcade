/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#include "Arcade.hpp"

Arcade::Arcade(const std::string &baselib)
{
    libname = baselib;
    if (baselib == "SFML")
        lib = std::shared_ptr<IGraphicLib>(new LibSFML());
    if (baselib == "NCURSES")
        lib = std::shared_ptr<IGraphicLib>(new LibNcurses());
}

Arcade::~Arcade()
{
}

int Arcade::loop()
{
    int on = 1;
    char input = 0;
    clock_t timer = 0;
    std::list<std::shared_ptr<IGameObject>> objects;
    if (!lib)
        return(84);

    while (on) {
        if ((clock() - timer) > (1000000 / 60)) {
            timer = clock();
            input = lib->getEvent();
            if (input == -2)
                return (0);
            if (input == -1)
                switchlib();
            game.handleEvents(input);
            game.updateGame();
            objects = game.getObjects();
            lib->draw(objects);
        }
    }
    return (0);
}

void Arcade::switchlib()
{
    if (libname == "NCURSES") {
        libname = "SFML";
        lib = std::shared_ptr<IGraphicLib>(new LibSFML());
    }
    else if (libname == "SFML") {
        libname = "NCURSES";
        lib = std::shared_ptr<IGraphicLib>(new LibNcurses());
    }
}

int main()
{
    Arcade arcade("SFML");
    return arcade.loop();
}