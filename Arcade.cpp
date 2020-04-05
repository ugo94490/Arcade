/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Arcade
*/

#include <iostream>
#include <sys/types.h>
#include <cstring>
#include "Exception.hpp"
#include "Encapsulation.hpp"
#include "Arcade.hpp"

Arcade::Arcade(std::string &baselib)
{
    DIR *games_dir = Encapsulation::fct_opendir("./games");
    DIR *lib_dir = Encapsulation::fct_opendir("./lib");
    struct dirent *file;
    std::string str;
    int i = -1;

    idx_lib = 0;
    idx_game = 0;
    idx_menu = 0;
    gamelib = NULL;
    liblib = NULL;
    menu = "LOL";
    while ((file = Encapsulation::fct_readdir(games_dir)) != NULL) {
        if (std::strncmp(file->d_name, "lib_arcade_", 11) == 0 || std::strncmp(file->d_name, "./lib_arcade_", 13) == 0) {
            list_game.push_back(file->d_name);
            i++;
            if (std::strcmp(file->d_name, "lib_arcade_menu.so") == 0 || std::strcmp(file->d_name, "./lib_arcade_menu.so") == 0) {
                menu = file->d_name;
                idx_menu = i;
            }
        }
    }
    while ((file = Encapsulation::fct_readdir(lib_dir)) != NULL) {
        if (std::strncmp(file->d_name, "lib_arcade_", 11) == 0 || std::strncmp(file->d_name, "./lib_arcade_", 13) == 0) {
            str = file->d_name;
            list_lib.push_back("lib/" + str);
        }
    }
    Encapsulation::fct_closedir(games_dir);
    Encapsulation::fct_closedir(lib_dir);
    std::srand(std::time(nullptr));
    if (list_game.size() < 1)
        throw(Exception ("No game found"));
    if (list_lib.size() < 1)
        throw(Exception ("No lib found"));
    gamename = "Arcade";
    loadlib(baselib);
    if (menu != "LOL") {
        idx_game = idx_menu;
        loadgame(list_game[idx_game]);
    } else
        loadgame(list_game[0]);
}

Arcade::~Arcade()
{
}

void Arcade::loadlib(const std::string &libstr)
{
    lib = 0;
    if (liblib)
        Encapsulation::fct_dlclose(liblib);
    liblib = Encapsulation::fct_dlopen(libstr.c_str(), RTLD_LAZY);
    if (!liblib)
        throw(Exception ("Lib " + libstr + " not found"));
    IGraphicLib *(*mkr)() = (IGraphicLib *(*)())Encapsulation::fct_dlsym(liblib, "makerlib");
    if (!mkr)
        throw(Exception ("Lib " + libstr + " constructor not found"));
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
        Encapsulation::fct_dlclose(gamelib);
    gamelib = Encapsulation::fct_dlopen(to_open.c_str(), RTLD_LAZY);
    if (!gamelib)
        throw(Exception ("Game " + gamename + " not found"));
    IGame *(*mkr)() = (IGame *(*)())Encapsulation::fct_dlsym(gamelib, "makergame");
    if (!mkr)
        throw(Exception ("Game " + gamename + " constructor not found"));
    game = std::shared_ptr<IGame>((mkr)());
    lib->loadGame(gamename);
}

void Arcade::highScore(int score)
{
    bool isnum = true;
    std::string line;
    std::fstream myfile ("./games/score.txt");

    if (!myfile.is_open())
        throw(Exception ("Could not open score.txt"));
    getline(myfile, line);
    myfile.close();
    std::ofstream myfile2("./games/score.txt");
    if (!myfile2.is_open())
        throw(Exception ("Could not open score.txt"));
    for (size_t idx = 0; idx != line.size(); idx++) {
        if (std::isdigit(line[idx]) == false) {
            isnum = false;
            break;
        }
    }
    if (line.size() > 0 && line.size() < 9 && isnum == true) {
        if (std::stoi(line) < score)
            myfile2 << score;
        else
            myfile2 << line;
    } else {
        myfile2 << score;
    }
    myfile2.close();
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
            if (input == -7) {
                idx_game = idx_menu;
                loadgame(list_game[idx_game]);
                input = 0;
            }
            if (input == -6) {
                loadgame(list_game[idx_game]);
                input = 0;
            }
            if (input == -3) {
                nextGame();
                input = 0;
            }
            if (input == -5) {
                prevGame();
                input = 0;
            }
            if (input == -2)
                return (0);
            if (input == -1) {
                nextLib();
                lib->init_score(score, pos);
            }
            if (input == -4) {
                prevLib();
                lib->init_score(score, pos);
            }
            if ((gameOver = game->handleEvents(input)) == 84)
                throw(Exception ("Error during runtime"));
            if (gameOver == 1) {
                lib->gameOver(game->getScore());
                highScore(game->getScore());
                idx_game = idx_menu;
                loadgame(list_game[idx_menu]);
            }
            game->updateGame();
            lib->draw(game);
            lib->draw_score(game->getScore(), pos);
        }
    }
    return (0);
}

void Arcade::nextGame()
{
    if (idx_game + 1 >= list_game.size())
        idx_game = 0;
    else
        idx_game++;
    loadgame(list_game[idx_game]);
}

void Arcade::prevGame()
{
    if (idx_game == 0)
        idx_game = list_game.size() - 1;
    else
        idx_game--;
    loadgame(list_game[idx_game]);  
}

void Arcade::nextLib()
{
    if (idx_lib + 1 >= list_lib.size())
        idx_lib = 0;
    else
        idx_lib++;
    loadlib(list_lib[idx_lib]);
}

void Arcade::prevLib()
{
    if (idx_lib == 0)
        idx_lib = list_lib.size() - 1;
    else
        idx_lib--;
    loadlib(list_lib[idx_lib]);
}

int Arcade::help(char *str)
{
    std::cout << "\nTo launch the game do the command " << str << " [GRAPHICAL LIB]" << std::endl;
    std::cout << std::endl;
    std::cout << "Keys :" << std::endl;
    std::cout << '\t' << "B to go back to menu" << std::endl;
    std::cout << '\t' << "R to restart the game" << std::endl;
    std::cout << '\t' << "P to go to previous Game" << std::endl;
    std::cout << '\t' << "N to go to next Game" << std::endl;
    std::cout << '\t' << "M to go to previous Graphical Lib" << std::endl;
    std::cout << '\t' << "Enter to go to next Graphical Lib" << std::endl;
    std::cout << '\t' << "Escape to quit " << str << std::endl;
    std::cout << '\t' << "Arrow Keys to move in each game" << std::endl;
    std::cout << '\t' << "In nibbler game only, press space to go faster\n" << std::endl;
    return (0);
}

int main(int ac, char **av, char **env)
{
    std::string str;
    try {
        if (*env == NULL)
            throw(Exception ("Environnement not found"));
        if (ac != 2)
            return (Arcade::help(av[0]));
        str = av[1];
        Arcade arcade(str);
        return (arcade.loop());
    } catch (Exception& err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
}