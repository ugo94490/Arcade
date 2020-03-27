/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include <fstream>
#include <string>
#include <ctime>
#include <unistd.h>
#include "Pacman.hpp"

using namespace std;

static Rect pacRects[11] = {
    {50, 72, 25, 25}, //playerfront
    {30, 95, 22, 22}, //maze
    {0, 0, 0, 0}, // qdoor
    {144, 144, 25, 25}, // ghost1up
    {144, 192, 25, 25}, // ghost2up
    {144, 216, 25, 25}, // ghost3up
    {335, 192, 25, 25}, // ghost4up
    {230, 1, 10, 10}, // star
    {0, 168, 22, 22}, // gold
    {0, 0, 0, 0} // space
};

static Rect pacAnim[9] = {
    {50, 72, 25, 25}, //left1
    {2, 72, 25, 25}, //left2
    {95, 72, 25, 25}, //right1
    {144, 72, 25, 25}, //right2
    {24, 74, 25, 25}, //up1
    {72, 74, 25, 25}, //up2
    {120, 72, 25, 25}, //down1
    {168, 72, 25, 25} //down2
};

static const Rect rightAnim[5] = {
    {95, 144, 25, 25},  //1right
    {95, 192, 25, 25},  //2right
    {95, 216, 25, 25},  //3right
    {287, 192, 25, 25}  //4right
};

static const Rect leftAnim[5] = {
    {24, 144, 25, 25},  //1left
    {24, 192, 25, 25},  //2left
    {24, 216, 25, 25},  //3left
    {215, 192, 25, 25}  //4left
};

static const Rect upAnim[5] = {
    {144, 144, 25, 25}, // ghost1up
    {144, 192, 25, 25}, // ghost2up
    {144, 216, 25, 25}, // ghost3up
    {335, 192, 25, 25} // ghost4up
};

static const Rect downAnim[5] = {
    {48, 144, 25, 25},  //1down
    {48, 192, 25, 25},  //2down
    {48, 216, 25, 25},  //3down
    {264, 192, 25, 25} //4down
};

static const char pacFlags[12] = "PX-RBOY*G ";

Pacman::Pacman()
{
    std::srand(std::time(nullptr));
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

bool Pacman::isPriority(std::shared_ptr<PacObject> ptr)
{
    if (ptr->getType() == PacObject::PLAYER || ptr->getType() == PacObject::RED ||
    ptr->getType() == PacObject::BLUE || ptr->getType() == PacObject::ORANGE ||
    ptr->getType() == PacObject::YELLOW)
        return true;
    return false;
}

std::list<std::shared_ptr<PacObject>> Pacman::initGame(void) const
{
    std::list<std::shared_ptr<PacObject>> tmpList;
    std::list<std::shared_ptr<PacObject>> list;
    std::shared_ptr<PacObject> ptr;
    string line;
    ifstream myfile ("./games/pacman/map.txt");

    if (!myfile.is_open())
        throw(std::string("Could not open pacman map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        for (int j = 0; line[j]; j++) {
            ptr = createObject(float(j) * 32.0, float(i) * 32.0, line[j]);
            if (ptr != NULL && (ptr->getType() == PacObject::PLAYER || ptr->getType() == PacObject::RED ||
            ptr->getType() == PacObject::BLUE || ptr->getType() == PacObject::ORANGE ||
            ptr->getType() == PacObject::YELLOW))
                list.push_front(ptr);
            else
                tmpList.push_front(ptr);
        }
    }
    myfile.close();
    for (auto it = tmpList.begin(); it != tmpList.end(); ++it)
        list.push_front(*it);
    return list;
}

std::list<std::shared_ptr<PacObject>> Pacman::filleObj()
{
    std::list<std::shared_ptr<PacObject>> obj;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::RED) {
            obj.push_back(*it);
            break;
        }
    }
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::BLUE) {
            obj.push_back(*it);
            break;
        }
    }
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::ORANGE) {
            obj.push_back(*it);
            break;
        }
    }
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::YELLOW) {
            obj.push_back(*it);
            break;
        }
    }
    return obj;
}

void Pacman::animPacman()
{
    if (idxAnimPac % 2 == 0) {
        pacRects[0] = pacAnim[idxAnimPac];
        idxAnimPac++;
    }
    else {
        pacRects[0] = pacAnim[idxAnimPac];
        idxAnimPac--;
    }
}

void Pacman::handleEvents(const unsigned char &c)
{
    size_t tmpDir = 0;
    std::list<std::shared_ptr<PacObject>> obj = filleObj();
    std::shared_ptr<PacObject> player;

    usleep(90000);
    ctr_ghost(obj);
    if (c < 1 || c > 4)
        tmpDir = _dir;
    else
        tmpDir = c;
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getType() == PacObject::PLAYER) {
            player = *it;
            break;
        }
    }
    if (!player)
        throw("Player does not exist");
    move_object(player, tmpDir);
    gameOver();
}

bool Pacman::gameOver()
{
    /* if (PacObject::getStar() == 0)
        return false; */
    return _lost;
}

std::shared_ptr<PacObject> Pacman::createObject(float posx, float posy, char c) const
{
    if (c != 'P' && c != 'X' && c != '*' && c != '-' && c != 'R' && c != 'B' && c != 'O' && c != 'Y' && c != 'G' && c != ' ')
        return NULL;
    auto ptr = std::make_shared<PacObject>(PacObject(posx, posy, c));
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
            break;
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
            if (type == PacObject::STAR || type == PacObject::GOLD) {
                *it = createObject(pos.first, pos.second, ' ');
                break;
            }
        }
    }
}

int randPos()
{
    return std::rand() % 4 + 1;
}

bool Pacman::checkColisionGhost(std::pair<float, float> pos)
{
    int type;

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (it->get()->getPos() == pos) {
            type = it->get()->getType();
            if (type == PacObject::PLAYER) {
                _lost = true;
                return false;
            }
            if (type == PacObject::WALL)
                return true;
            break;
        }
    }
    return false;
}

std::pair<float, float> Pacman::findDirection(std::shared_ptr<PacObject> obj, int dir, int idx)
{
    std::pair<float, float> pos;
    static Rect tmp[1] = {0,0,0,0};

    if (dir == 1) {
        pos = std::pair<float, float>(obj->getPos().first - 32.0, obj->getPos().second);
        tmp[0] = rightAnim[idx];
    }
    if (dir == 2) {
        pos = std::pair<float, float>(obj->getPos().first + 32.0, obj->getPos().second);
        tmp[0] = leftAnim[idx];
    }
    if (dir == 3) {
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second - 32.0);
        tmp[0] = upAnim[idx];
    }
    if (dir == 4) {
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second + 32.0);
        tmp[0] = downAnim[idx];
    }
    if (checkColisionGhost(pos) == true)
        return findDirection(obj, randPos(), idx);
    else {
        pacRects[idx+3] = tmp[0];
        return pos;
    }
}

void Pacman::ctr_ghost(std::list<std::shared_ptr<PacObject>> obj)
{
    int idx = 0;
    std::shared_ptr<PacObject> tmp;

    for (auto it = obj.begin(); idx != 4; ++it) {
        tmp = *it;
        tmp->setPos(findDirection(*it, randPos(), idx));
        idx++;
    }
}

std::pair<float, float> Pacman::checkDoor(std::pair<float, float> pos)
{
    std::pair<float, float> doorL = std::pair<float, float>(0.0, 416.0);
    std::pair<float, float> doorR = std::pair<float, float>(640.0, 416.0);

    if (pos == doorR)
        return std::pair<float, float>(32.0, 416.0);
    if (pos == doorL)
        return std::pair<float, float>(608.0, 416.0);
    return pos;
}

int Pacman::move_object(std::shared_ptr<PacObject> obj, int direction)
{
    static int oldDir = 0;
    std::pair<float, float> pos;

    if (direction == 1) {
        pos = std::pair<float, float>(obj->getPos().first - 32.0, obj->getPos().second);
        if (oldDir != direction)
            idxAnimPac = 0;
    }
    if (direction == 2) {
        pos = std::pair<float, float>(obj->getPos().first + 32.0, obj->getPos().second);
        if (oldDir != direction)
            idxAnimPac = 2;
    }
    if (direction == 3) {
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second - 32.0);
        if (oldDir != direction)
            idxAnimPac = 4;
    }
    if (direction == 4) {
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second + 32.0);
        if (oldDir != direction)
            idxAnimPac = 6;
    }
    oldDir = direction;
    if (checkColision(pos) == true)
        return (1);
    checkStar(pos);
    pos = checkDoor(pos);
    obj->setPos(pos);
    _dir = direction;
    if (oldDir != direction)
        pacRects[0] = pacAnim[idxAnimPac];
    else
        animPacman();
    return (0);
}

char Pacman::getAppearanceCharIdx(int idx)
{
    return pacFlags[idx];
}

Rect Pacman::getAppearanceRectIdx(int idx)
{
    return pacRects[idx];
}