/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include "Exception.hpp"
#include "Arcade.hpp"

Arcade::Arcade(std::string &baselib)
{
    DIR *games_dir = opendir("./games");
    DIR *lib_dir = opendir("./lib");
    struct dirent *file;
    std::string str;

    idx_lib = 0;
    idx_game = 0;
    gamelib = NULL;
    liblib = NULL;
    if (lib_dir == NULL || games_dir == NULL)
        throw(Exception ("Can't open lib or games directory"));
    while ((file = readdir(games_dir)) != NULL) {
        if (std::strncmp(file->d_name, "lib_arcade_", 11) == 0)
            list_game.push_back(file->d_name);
    }
    while ((file = readdir(lib_dir)) != NULL) {
        if (std::strncmp(file->d_name, "lib_arcade_", 11) == 0)
            list_lib.push_back(file->d_name);
    }
    std::srand(std::time(nullptr));
    if (list_game.size() < 1)
        throw(Exception ("No game found"));
    if (list_lib.size() < 1)
        throw(Exception ("No lib found"));
    gamename = "Arcade";
    loadlib(baselib.erase(0, 4));
    //loadgame("menu");
    loadgame(list_game[0]);
}

Arcade::~Arcade()
{
}

void Arcade::loadlib(const std::string &libstr)
{
    libname = libstr;
    lib = 0;
    libname.erase(0, 11);
    libname.erase(libname.size() - 3, 3);
    std::string to_open = "lib/" + libstr;
    if (liblib)
        dlclose(liblib);
    liblib = dlopen(to_open.c_str(), RTLD_LAZY);
    if (!liblib)
        throw(Exception ("Lib " + libname + " not found"));
    IGraphicLib *(*mkr)() = (IGraphicLib *(*)())dlsym(liblib, "maker");
    if (!mkr)
        throw(Exception ("Lib " + libname + " constructor not found"));
    lib = std::shared_ptr<IGraphicLib>((mkr)());
    if (gamename != "Arcade")
        lib->loadGame(gamename);
}

void Arcade::loadgame(const std::string &gamestr)
{
    gamename = gamestr;
    game = 0;
    gamename.erase(0, 11);
    gamename.erase(gamename.size() - 3, 3);
    std::string to_open = "games/" + gamestr;
    if (gamelib)
        dlclose(gamelib);
    gamelib = dlopen(to_open.c_str(), RTLD_LAZY);
    if (!gamelib)
        throw(Exception ("Game " + gamename + " not found"));
    IGame *(*mkr)() = (IGame *(*)())dlsym(gamelib, "maker");
    if (!mkr)
        throw(Exception ("Game " + gamename + " constructor not found"));
    game = std::shared_ptr<IGame>((mkr)());
    lib->loadGame(gamename);
}

int Arcade::loop()
{
    int gameOver = 0;
    int on = 1;
    char input = 0;
    clock_t timer = 0;
    int score = 0;
    std::list<std::shared_ptr<IGameObject>> objects;
    std::pair<float, float> pos = {1000, 100};

    if (!lib)
        return(84);
    lib->init_score(score, pos);
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
            if (input == -1) {
                switchlib();
                lib->init_score(score, pos);
            }
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
    if (idx_game + 1 >= list_game.size())
        idx_game = 0;
    else
        idx_game++;
    loadgame(list_game[idx_game]);
}

void Arcade::switchlib()
{
    if (idx_lib + 1 >= list_lib.size())
        idx_lib = 0;
    else
        idx_lib++;
    loadlib(list_lib[idx_lib]);
}

int main(int ac, char **av)
{
    std::string str;
    try {
        if (ac != 2)
            throw(Exception("Only one argument required"));
        str = av[1];
        Arcade arcade(str);
        return (arcade.loop());
    } catch (Exception& err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
}