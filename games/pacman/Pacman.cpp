/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include <fstream>
#include <string>
#include "Pacman.hpp"

using namespace std;

static const Rect pacRects[2] = {
    {192, 0, 64, 64},
    {64, 0, 64, 64}
};

static const char pacFlags[8] = "PX*OQG ";

Pacman::Pacman()
{
    objects = initGame();
}

Pacman::~Pacman()
{
}

std::list<std::shared_ptr<IGameObject>> Pacman::getObjects(void) const
{
    std::list<std::shared_ptr<IGameObject>> list;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        list.push_back(*it);
    }
    return (list);
}

std::list<std::shared_ptr<PacObject>> Pacman::initGame(void) const
{
    std::list<std::shared_ptr<PacObject>> list;
    std::shared_ptr<PacObject> ptr;
    string line;
    ifstream myfile ("./games/pacman/map");

    if (!myfile.is_open())
        throw(std::string("Could not open pacman map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        for (int j = 0; line[j]; j++) {
            ptr = createObject(float(j) * 64.0, float(i) * 64.0, line[j]);
            if (ptr)
                list.push_front(ptr);
        }
    }
    myfile.close();
    return list;
}

void Pacman::handleEvents(const unsigned char &c)
{
    std::shared_ptr<PacObject> player = NULL;

    if (c < 1 || c > 4)
        return;
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (!player)
        throw("Player does not exist");
    move_object(player, c);
}

std::shared_ptr<PacObject> Pacman::createObject(float posx, float posy, char c) const
{
    if (c != 'P' && c != 'X' && c != '*' && c != 'O' && c != 'Q' && c != ' ')
        return NULL;
    std::shared_ptr<PacObject> ptr(new PacObject(posx, posy, c));
    return (ptr);
}

bool Pacman::checkColision(std::pair<float, float> pos)
{
    int type;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getPos() == pos) {
            type = it->get()->getType();
            if (type == PacObject::WALL || type == PacObject::GDOOR)
                return true;
        }
    }
    return false;
}

void Pacman::checkStar(std::pair<float, float> pos)
{
    int type;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getPos() == pos) {
            type = it->get()->getType();
            if (type == PacObject::STAR) {
                *it = createObject(pos.first, pos.second, ' ');
                break;
            }
        }
    }
}

int Pacman::move_object(std::shared_ptr<PacObject> obj, int direction)
{
    std::shared_ptr<PacObject> blocking;
    std::pair<float, float> pos;

    if (direction == 1)
        pos = std::pair<float, float>(obj->getPos().first - 64.0, obj->getPos().second);
    if (direction == 2)
        pos = std::pair<float, float>(obj->getPos().first + 64.0, obj->getPos().second);
    if (direction == 3)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second - 64.0);
    if (direction == 4)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second + 64.0);

    if (!obj)
        return (0);
    if (checkColision(pos) == true)
        return (1);
    checkStar(pos);
    obj->setPos(pos);
    return (0);
}

char Pacman::getAppearanceCharIdx(int idx)
{
    /* if (idx > 1 || idx < 0)
        return ' '; */
    return pacFlags[idx];
}

Rect Pacman::getAppearanceRectIdx(int idx)
{
    /* if (idx > 7 || idx < 0)
        return {0, 0, 0, 0}; */
    return pacRects[idx];
}