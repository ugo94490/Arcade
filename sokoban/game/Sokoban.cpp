/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sokoban
*/

#include <fstream>
#include <string>
#include "Sokoban.hpp"

using namespace std;

Sokoban::Sokoban()
{
    objects = initGame();
}

Sokoban::~Sokoban()
{
}

std::list<std::shared_ptr<IGameObject>> Sokoban::getObjects(void) const
{
    std::list<std::shared_ptr<IGameObject>> list;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        list.push_back(*it);
    }
    return (list);
}

std::list<std::shared_ptr<SokoObject>> Sokoban::initGame(void) const
{
    std::list<std::shared_ptr<SokoObject>> list;
    std::shared_ptr<SokoObject> ptr;
    string line;
    ifstream myfile ("./game/map");

    if (!myfile.is_open())
        return list;
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

void Sokoban::handleEvents(const unsigned char &c)
{
    std::shared_ptr<SokoObject> player = NULL;

    if (c < 1 || c > 4)
        return;
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == SokoObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (!player)
        return;
    move_object(player, c);
}

std::shared_ptr<SokoObject> Sokoban::createObject(float posx, float posy, char c) const
{
    if (c != '#' && c != 'O' && c != 'X' && c != 'P')
        return NULL;
    std::shared_ptr<SokoObject> ptr(new SokoObject(posx, posy, c));
    return (ptr);
}

std::shared_ptr<SokoObject> Sokoban::check_free(std::pair<float, float> pos) const
{
    int type;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getPos() == pos) {
            type = it->get()->getType();
            if (type == SokoObject::CRATE || type == SokoObject::WALL)
                return (*it);
        }
    }
    return (NULL);
}

int Sokoban::move_object(std::shared_ptr<SokoObject> obj, int direction)
{
    std::shared_ptr<SokoObject> blocking;
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
    if (obj->getType() == SokoObject::CRATE) {
        if ((blocking = check_free(pos)) == NULL) {
            obj->setPos(pos);
            return (1);
        }
        return (0);
    }
    if (obj->getType() == SokoObject::PLAYER) {
        if ((blocking = check_free(pos)) == NULL) {
            obj->setPos(pos);
            return (1);
        }
        else if (move_object(blocking, direction)) {
            obj->setPos(pos);
            return (1);
        }
        return (0);
    }
    return (0);
}