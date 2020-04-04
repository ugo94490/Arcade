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

    if (ch == 'r')
        return (-6);
    if (ch == 'p')
        return (-5);
    if (ch == 'm')
        return (-4);
    if (ch == 110)
        return (-3);
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
    if (ch == 32)
        return (5);
    return (0);
}

void LibNcurses::draw(std::shared_ptr<IGame> game)
{
    std::list<std::shared_ptr<IGameObject>> objects = game->getObjects();
    std::pair<float, float> pos;
    float scale = 32;
    erase();
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        pos = it->get()->getPos();
        if ((int)pos.first % 32 != 0 || (int)pos.second % 32 != 0) {
            scale = 16;
            break;
        }
    }
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        pos = it->get()->getPos();
        if (int(pos.first/scale) < COLS && int(pos.second/scale) < LINES && pos.first >= 0.0 && pos.second >= 0.0) {
            move(int(pos.second/scale), int(pos.first/scale));
            printw("%c", game->getAppearanceCharIdx(it->get()->getAppearance()));
        }
    }
}

void LibNcurses::draw_score(int score, std::pair<float, float> pos)
{
    (void)pos;
    move((LINES / 2), (COLS / 4) * 3);
    printw("%s\n", ("Score : " + std::to_string(score)).c_str());
}

void LibNcurses::gameOver(int score)
{
    static clock_t timer = clock();
    erase();
    move((LINES / 2) - 1, (COLS / 2) - 4);
    printw("%s\n", "GameOver");
    move((LINES / 2), (COLS / 2) - (std::to_string(score).size() / 2));
    printw("%s\n", ("Score : " + std::to_string(score)).c_str());
    while (clock() - timer <= 6000000) {
    }
}

void LibNcurses::init_score(int score, std::pair<float, float> pos)
{

}