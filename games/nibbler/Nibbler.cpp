/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include <fstream>
#include <string>
#include <vector>
#include "Exception.hpp"
#include "nibbler.hpp"

using namespace std;

static const Rect NibRects[5] = {
    {192, 0, 64, 64},
    {64, 0, 64, 64},
    {256, 0, 64, 64},
    {0, 0, 64, 64},
    {192, 0, 64, 64}
};

static const char NibChars[6] = "P#x T";

Nibbler::Nibbler()
{
    objects = initGame();
    nb_fruit = 0;
    score = 0;
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

std::vector<std::pair<float, float>> Nibbler::fill_pair(std::shared_ptr<NibObject> old_ptr) const
{
    std::vector<std::pair<float, float>> pos;
    std::pair<float, float> tmp;

    tmp = std::pair<float, float>(old_ptr->getPos().first - 32.0, old_ptr->getPos().second);
    pos.push_back(tmp);
    tmp = std::pair<float, float>(old_ptr->getPos().first + 32.0, old_ptr->getPos().second);
    pos.push_back(tmp);
    tmp = std::pair<float, float>(old_ptr->getPos().first, old_ptr->getPos().second - 32.0);
    pos.push_back(tmp);
    tmp = std::pair<float, float>(old_ptr->getPos().first, old_ptr->getPos().second + 32.0);
    pos.push_back(tmp);
    return (pos);
}

std::vector<std::pair<float, float>> Nibbler::check_dispo(std::vector<std::pair<float, float>> pos, std::list<std::shared_ptr<NibObject>> obj) const
{
    std::vector<std::pair<float, float>> dispo;
    int j = 0;
    int tab[4] = {0, 0, 0, 0};

    for (auto i = obj.begin(); i != obj.end(); i++, j++) {
        if (i->get()->getPos() == pos[0] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[0]++;
        if (i->get()->getPos() == pos[1] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[1]++;
        if (i->get()->getPos() == pos[2] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[2]++;
        if (i->get()->getPos() == pos[3] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[3]++;
    }
    if (tab[0] == 1)
        dispo.push_back(pos[0]);
    if (tab[1] == 1)
        dispo.push_back(pos[1]);
    if (tab[2] == 1)
        dispo.push_back(pos[2]);
    if (tab[3] == 1)
        dispo.push_back(pos[3]);
    return (dispo);
}

std::list<std::shared_ptr<NibObject>> Nibbler::new_body(std::shared_ptr<NibObject> old_ptr, std::list<std::shared_ptr<NibObject>> obj, int count) const
{
    std::vector<std::pair<float, float>> pos = fill_pair(old_ptr);
    std::vector<std::pair<float, float>> dispo = check_dispo(pos, obj);
    std::shared_ptr<NibObject> new_ptr;
    int idx = 0;

    if (dispo.size() == 0)
        throw(Exception ("Pas assez de place pour créer le serpent"));
    if (dispo.size() != 1)
        idx = rand() % (dispo.size() - 1);
    else
        idx = 0;
    new_ptr = createObject(float(dispo[idx].first), float(dispo[idx].second), 'T');
    obj.push_back(new_ptr);
    count++;
    if (count != 3)
        obj = new_body(new_ptr, obj, count);
    return (obj);
}

int Nibbler::getDir(std::shared_ptr<NibObject> player, std::list<std::shared_ptr<NibObject>> obj) const
{
    std::vector<std::pair<float, float>> pos;
    int j = 0;
    int tab[4] = {0, 0, 0, 0};

    if (!player)
        throw(Exception ("Player does not exist"));
    pos = fill_pair(player);
    for (auto i = obj.begin(); i != obj.end(); i++, j++) {
        if (i->get()->getPos() == pos[0] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[0]++;
        if (i->get()->getPos() == pos[1] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[1]++;
        if (i->get()->getPos() == pos[2] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[2]++;
        if (i->get()->getPos() == pos[3] && (i->get()->getType() == NibObject::FLOOR || i->get()->getType() == NibObject::TAIL))
            tab[3]++;
    }
    if (tab[0] == 1)
        return (1);
    if (tab[1] == 1)
        return (2);
    if (tab[2] == 1)
        return (3);
    if (tab[3] == 1)
        return (4);
    return (0);
}

std::list<std::shared_ptr<NibObject>> Nibbler::generatePlayer(std::list<std::shared_ptr<NibObject>> obj)
{
    std::list<std::shared_ptr<NibObject>>::iterator it = obj.begin();
    std::shared_ptr<NibObject> ptr;
    std::shared_ptr<NibObject> player;
    std::pair<float, float> pos;

    std::advance(it, (obj.size() - 1) / 2);
    pos = it->get()->getPos();
    ptr = createObject(float(pos.first), float(pos.second), 'P');
    player = ptr;
    obj.push_back(ptr);
    obj = new_body(ptr, obj, 0);
    direction = getDir(ptr, obj);
    prev_dir = direction;
    return (obj);
}

std::list<std::shared_ptr<NibObject>> Nibbler::initGame(void)
{
    std::list<std::shared_ptr<NibObject>> list;
    std::shared_ptr<NibObject> ptr;
    string line;
    ifstream myfile ("./games/nibbler/map/map.txt");
    std::pair<float, float> pos;

    if (!myfile.is_open())
        throw(Exception ("Could not open Nibbler map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        for (int j = 0; line[j]; j++) {
            ptr = createObject(float(j) * 32.0, float(i) * 32.0, line[j]);
            if (ptr)
                list.push_front(ptr);
        }
    }
    if (list.size() == 0)
        throw(Exception ("Map is empty"));
    list = generatePlayer(list);
    myfile.close();
    return list;
}

int Nibbler::check_dir(int direction)
{
    std::shared_ptr<NibObject> player = NULL;
    std::pair<float, float> pos;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == NibObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (direction == 1)
        pos = std::pair<float, float>(player->getPos().first - 32.0, player->getPos().second);
    if (direction == 2)
        pos = std::pair<float, float>(player->getPos().first + 32.0, player->getPos().second);
    if (direction == 3)
        pos = std::pair<float, float>(player->getPos().first, player->getPos().second - 32.0);
    if (direction == 4)
        pos = std::pair<float, float>(player->getPos().first, player->getPos().second + 32.0);
    for (auto it = objects.begin(); it != objects.end(); ++it)
        if (it->get()->getPos() == pos && it->get()->getType() == NibObject::TAIL)
            return (84);
    return (0);
}

int Nibbler::getScore()
{
    return (score);
}

int Nibbler::handleEvents(const unsigned char &c)
{
    static clock_t timer = 0;
    static float mult = 1;
    std::shared_ptr<NibObject> player = NULL;

    if (c == 5) {
        if (mult >= 0.2)
            mult -= 0.10;
        return (0);
    }
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == NibObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (!player)
        throw(Exception ("Player does not exist"));
    if ((clock() - timer) > (1000000 * mult)) {
        if (!(c < 1 || c > 4))
            if (check_dir(c) == 0) {
                prev_dir = direction;
                direction = c;
            }
        timer = clock();
        score++;
        return (move_object(player, direction));
    } else if (!(c < 1 || c > 4)) {
        if (check_dir(c) == 0) {
            prev_dir = direction;
            direction = c;
        }
        return (0);
    }
    return (0);
}

void Nibbler::SetRandItems(void)
{
    size_t idx = rand() % (objects.size() - 1);
    std::list<std::shared_ptr<NibObject>>::iterator it = objects.begin();
    std::shared_ptr<NibObject> ptr;
    
    std::advance(it, idx);
    while (it->get()->getType() == NibObject::PLAYER || it->get()->getType() == NibObject::WALL || it ->get()->getType() == NibObject::TAIL) {
        idx = rand() % (objects.size() - 1);
        it = objects.begin();
        std::advance(it, idx);
    }
    ptr = createObject(it->get()->getPos().first, it->get()->getPos().second, ' ');
    ptr->setAppearance(NibObject::STAR);
    ptr->setType(NibObject::STAR);
    objects.push_back(ptr);
    nb_fruit += 1;
}

std::shared_ptr<NibObject> Nibbler::createObject(float posx, float posy, char c) const
{
    if (c != '#' && c != 'P' && c != ' ' && c != 'T')
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
            if (type == NibObject::WALL || type == NibObject::STAR || type == NibObject::TAIL)
                return (*it);
        }
    }
    return (NULL);
}

int Nibbler::move_snake(std::shared_ptr<NibObject> obj, std::pair<float, float> pos) const
{
    std::pair<float, float> prev = obj->getPos();
    std::pair<float, float> tmp;

    obj->setPos(pos);
    for (auto it = objects.begin(); it != objects.end(); it++) {
        if (it->get()->getType() == NibObject::TAIL) {
            tmp = it->get()->getPos();
            it->get()->setPos(prev);
            prev = tmp;
        }
    }
    return (0);
}

int Nibbler::moveAdd_snake(std::shared_ptr<NibObject> obj, std::pair<float, float> pos)
{
    std::pair<float, float> prev = obj->getPos();
    std::pair<float, float> tmp;
    std::shared_ptr<NibObject> new_ptr;

    obj->setPos(pos);
    for (auto it = objects.begin(); it != objects.end(); it++) {
        if (it->get()->getType() == NibObject::TAIL) {
            tmp = it->get()->getPos();
            it->get()->setPos(prev);
            prev = tmp;
        }
    }
    new_ptr = createObject(float(prev.first), float(prev.second), 'T');
    objects.push_back(new_ptr);
    return (0);
}

int Nibbler::move_object(std::shared_ptr<NibObject> obj, int direction)
{
    std::shared_ptr<NibObject> blocking;
    std::pair<float, float> pos;
    std::shared_ptr<NibObject> ptr;

    if (direction == 1)
        pos = std::pair<float, float>(obj->getPos().first - 32.0, obj->getPos().second);
    if (direction == 2)
        pos = std::pair<float, float>(obj->getPos().first + 32.0, obj->getPos().second);
    if (direction == 3)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second - 32.0);
    if (direction == 4)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second + 32.0);
    if (!obj)
        return (1);
    if (obj->getType() == NibObject::PLAYER) {
        if ((blocking = check_free(pos)) == NULL)
            return (move_snake(obj, pos));
        else if (blocking->getType() == NibObject::TAIL)
            return (0);
        else if (blocking->getType() == NibObject::STAR) {
            nb_fruit -= 1;
            ptr = createObject(blocking->getPos().first, blocking->getPos().second, ' ');
            moveAdd_snake(obj, pos);
            objects.remove(blocking);
            objects.push_front(ptr);
            return (0);
        }
        return (1);
    }
    return (1);
}

char Nibbler::getAppearanceCharIdx(int idx)
{
    if (idx > 4 || idx < 0)
        return ' ';
    return NibChars[idx];
}

Rect Nibbler::getAppearanceRectIdx(int idx)
{
    if (idx > 4 || idx < 0)
        return {0, 0, 0, 0};
    return NibRects[idx];
}

void Nibbler::updateGame()
{
    if (nb_fruit < 2)
        SetRandItems();
}