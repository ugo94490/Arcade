/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include <fstream>
#include <string>
#include "nibbler.hpp"

using namespace std;

static const Rect NibRects[2] = {
    {192, 0, 64, 64},
    {64, 0, 64, 64}
};

static const char NibChars[3] = "P#";

Nibbler::Nibbler()
{
    objects = initGame();
}

Nibbler::~Nibbler()
{
}

std::list<std::shared_ptr<IGameObject>> Nibbler::getObjects(void) const
{
    std::list<std::shared_ptr<IGameObject>> list;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        list.push_back(*it);
    }
    return (list);
}

std::list<std::shared_ptr<NibObject>> Nibbler::initGame(void) const
{
    std::list<std::shared_ptr<NibObject>> list;
    std::shared_ptr<NibObject> ptr;
    string line;
    ifstream myfile ("./games/nibbler/map/map.txt");

    if (!myfile.is_open())
        throw(std::string("Could not open Nibbler map"));
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

void Nibbler::handleEvents(const unsigned char &c)
{
    std::shared_ptr<NibObject> player = NULL;

    if (c < 1 || c > 4)
        return;
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == NibObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (!player)
        throw("Player does not exist");
    move_object(player, c);
}

std::shared_ptr<NibObject> Nibbler::createObject(float posx, float posy, char c) const
{
    if (c != '#' && c != 'P')
        return NULL;
    std::shared_ptr<NibObject> ptr(new NibObject(posx, posy, c));
    return (ptr);
}

std::shared_ptr<NibObject> Nibbler::check_free(std::pair<float, float> pos) const
{
    int type;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getPos() == pos) {
            type = it->get()->getType();
            if (type == NibObject::WALL)
                return (*it);
        }
    }
    return (NULL);
}

int Nibbler::move_object(std::shared_ptr<NibObject> obj, int direction)
{
    std::shared_ptr<NibObject> blocking;
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
    if (obj->getType() == NibObject::PLAYER) {
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

char Nibbler::getAppearanceCharIdx(int idx)
{
    if (idx > 1 || idx < 0)
        return ' ';
    return NibChars[idx];
}

Rect Nibbler::getAppearanceRectIdx(int idx)
{
    if (idx > 1 || idx < 0)
        return {0, 0, 0, 0};
    return NibRects[idx];
}