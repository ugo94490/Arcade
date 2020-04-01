/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#include <iostream>
#include "Arcade.hpp"

Arcade::Arcade(const std::string &baselib)
{
    std::srand(std::time(nullptr));
    gamename = "Arcade";
    loadlib(baselib);
    loadgame("pacman");
}

Arcade::~Arcade()
{
}

void Arcade::loadlib(const std::string &libstr)
{
    libname = libstr;
    std::string to_open = "./lib/lib_arcade_" + libstr + ".so";
    void *liblib = dlopen(to_open.c_str(), RTLD_LAZY);
    if (!liblib)
        throw(std::string("Lib " + libname + " not found"));
    IGraphicLib *(*mkr)() = (IGraphicLib *(*)())dlsym(liblib, "maker");
    if (!mkr)
        throw(std::string("Lib " + libname + " constructor not found"));
    lib = std::shared_ptr<IGraphicLib>((mkr)());
    if (gamename != "Arcade")
        lib->loadGame(gamename);
}

void Arcade::loadgame(const std::string &gamestr)
{
    gamename = gamestr;
    std::string to_open = "./games/game_" + gamestr + ".so";
    void *gamelib = dlopen(to_open.c_str(), RTLD_LAZY);
    if (!gamelib)
        throw(std::string("Game " + gamename + " not found"));
    IGame *(*mkr)() = (IGame *(*)())dlsym(gamelib, "maker");
    if (!mkr)
        throw(std::string("Game " + gamename + " constructor not found"));
    game = std::shared_ptr<IGame>((mkr)());
    lib->loadGame(gamename);
}

int Arcade::loop()
{
    int gameOver = 0;
    int on = 1;
    char input = 0;
    clock_t timer = 0;
    std::list<std::shared_ptr<IGameObject>> objects;
    std::pair<float, float> pos = {1000, 100};

    if (!lib)
        return(84);
    while (on) {
        if ((clock() - timer) > (1000000 / 60)) {
            timer = clock();
            input = lib->getEvent();
            if (input == -3) {
                switchgame();
                input = 0;
            }
            if (input == -2)
                return (0);
            if (input == -1)
                switchlib();
            if ((gameOver = game->handleEvents(input)) == 84)
                return (84);
            if (gameOver == 1) {
                lib->gameOver(game->getScore());
                break;
            }
            game->updateGame();
            lib->draw(game);
            lib->draw_score(game->getScore(), pos);
        }
    }
    return (0);
}

void Arcade::switchgame()
{
    if (gamename == "nibbler") {
        gamename = "sokoban";
        loadgame(gamename);
    } else if (gamename == "sokoban") {
        gamename = "pacman";
        loadgame(gamename);
    } else if (gamename == "pacman") {
        gamename = "nibbler";
        loadgame(gamename);
    }
}

void Arcade::switchlib()
{
    if (libname == "ncurses")
        loadlib("sfml");
    else if (libname == "sfml")
        loadlib("sdl");
    else if (libname == "sdl")
        loadlib("ncurses");
}

int main()
{
    try {
        Arcade arcade("sfml");
        return arcade.loop();
    } catch (std::string err) {
        std::cerr << err << std::endl;
        return (84);
    }
}