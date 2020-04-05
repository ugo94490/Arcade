/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CorePacman
*/

#include <fstream>
#include <string>
#include <unistd.h>
#include "Exception.hpp"
#include "Menu.hpp"


static Rect menuRects[23] = {
    {60, 48, 40, 40}, //M
    {108, 48, 40, 40},  //E
    {156, 48, 40, 40}, //N
    {202, 48, 55, 55},  //U
    {111, 113, 20, 40},  //I
    {145, 113, 25, 40},  //B
    {180, 113, 40, 40},  //L
    {225, 113, 40, 40},  //R
    {266, 113, 40, 40},  //P
    {300, 113, 40, 40},  //A
    {350, 113, 40, 40},  //C
    {397, 113, 40, 40},  //Q
    {447, 113, 40, 40},  //X
    {489, 113, 35, 40},  //S
    {528, 113, 40, 40},  //O
    {574, 113, 25, 40},  //K
    {617, 113, 40, 40},  //T
    {63, 169, 15, 15},  //-
    {105, 150, 40, 40},  //|
    {69, 215, 40, 40},  //F
    {110, 215, 40, 40},  //D
    {0, 0, 0, 0}        // ' '
};


static const char menuFlags[23] = "MENUIBLRPACQXSOKT-|FD ";


Menu::Menu()
{
    objects = initGame();
}

Menu::~Menu()
{
}

int Menu::getScore() const
{
    return _score;
}

int Menu::getBlockSize() const
{
    return 32;
}

void Menu::highScore()
{
    bool isnum = true;
    std::string line;
    std::fstream myfile ("./games/score.txt");

    if (!myfile.is_open())
        throw(Exception ("Could not open score.txt"));
    getline(myfile, line);
    for (size_t idx = 0; idx != line.size(); idx++) {
        if (std::isdigit(line[idx]) == false) {
            isnum = false;
            break;
        }
    }
    if (line.size() > 0 && line.size() < 9 && isnum == true) {
        _score = std::stoi(line);
    }
    else if (line.size() >= 9 && isnum == true) {
        _score = 99999999;
    }
    else if (isnum == false) {
        _score = 0;
    }
    myfile.close();
}

std::list<std::shared_ptr<IGameObject>> Menu::getObjects(void) const
{
    std::list<std::shared_ptr<IGameObject>> list;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        list.push_back(*it);
    }
    return (list);
}

std::list<std::shared_ptr<MenuObject>> Menu::initGame(void)
{
    std::list<std::shared_ptr<MenuObject>> list;
    std::shared_ptr<MenuObject> ptr;
    std::string line;
    std::ifstream myfile ("./games/menu/map.txt");

    highScore();
    if (!myfile.is_open())
        throw(Exception ("Could not open menu map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        for (int j = 0; line[j]; j++) {
            ptr = createObject(float(j) * 16.0, float(i) * 16.0, line[j]);
            if (ptr != NULL)
                list.push_front(ptr);
        }
    }
    myfile.close();
    return list;
}

int Menu::handleEvents(const unsigned char &c)
{
    (void) c;
   return 0;
}

std::shared_ptr<MenuObject> Menu::createObject(float posx, float posy, char c) const
{
    if (c != 'M' && c != 'E' && c != 'N' && c != 'U' && c != 'I' && c != 'B' && c != 'L' && c != 'R'
    && c != 'P' && c != 'A' && c != 'C' && c != 'Q' && c != 'X' && c != 'S' && c != 'O' && c != 'K'
    && c != 'T' && c != '-' && c != '|' && c != 'F' && c != 'D' && c != ' ')
        return NULL;
    auto ptr = std::make_shared<MenuObject>(MenuObject(posx, posy, c));
    return (ptr);
}

char Menu::getAppearanceCharIdx(int idx)
{
    return menuFlags[idx];
}

Rect Menu::getAppearanceRectIdx(int idx)
{
    return menuRects[idx];
}