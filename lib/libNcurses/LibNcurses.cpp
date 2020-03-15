/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** LibNcurses
*/

#include <iostream>
#include "LibNcurses.hpp"

LibNcurses::LibNcurses()
{
    window = initscr();
    noecho();
    raw();
    nodelay(window, true);
    keypad(stdscr, TRUE);
}

LibNcurses::~LibNcurses()
{
    endwin();
}

void LibNcurses::loadGame(const std::string &gamename)
{
}

char LibNcurses::getEvent()
{
    int ch = getch();

    if (ch == 27)
        return (-2);
    if (ch == 10)
        return (-1);
    if (ch == KEY_LEFT)
        return (1);
    if (ch == KEY_RIGHT)
        return (2);
    if (ch == KEY_UP)
        return (3);
    if (ch == KEY_DOWN)
        return (4);
    return (0);
}

void LibNcurses::draw(std::shared_ptr<IGame> game)
{
    std::list<std::shared_ptr<IGameObject>> objects = game->getObjects();
    std::pair<float, float> pos;
    erase();

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        pos = it->get()->getPos();
        if (int(pos.first/64.0) < COLS && int(pos.second/64.0) < LINES && pos.first >= 0.0 && pos.second >= 0.0) {
            move(int(pos.second/64.0), int(pos.first/64.0));
            printw("%c", game->getAppearanceCharIdx(it->get()->getAppearance()));
        }
    }
}
