/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CorePacman
*/

#include <fstream>
#include <string>
#include <ctime>
#include <unistd.h>
#include "Pacman.hpp"
#include "Backtrack.hpp"

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

static const Rect deadAnim[2] = {
    {144, 96, 25, 25}
};

static const char pacFlags[12] = "PX-RBOY*G ";

Pacman::Pacman()
{
    std::srand(std::time(nullptr));
    objects = initGame();
    _curPos.push_back(std::pair<float, float>(10.0 * 32, 10.0 * 32));
    _curPos.push_back(std::pair<float, float>(9.0 * 32, 13.0 * 32));
    _curPos.push_back(std::pair<float, float>(10.0 * 32, 13.0 * 32));
    _curPos.push_back(std::pair<float, float>(11.0 * 32, 13.0 * 32));
    _pacPos = std::pair<float, float>(10.0 * 32, 20.0 * 32);
    _jailPos = std::pair<float, float>(11.0 * 32, 12.0 * 32);
    _ghostPath.resize(4);
    _ghostPath[0].push_back(_curPos[0]);
    _ghostPath[1].push_back(_curPos[1]);
    _ghostPath[2].push_back(_curPos[2]);
    _ghostPath[3].push_back(_curPos[3]);
}



Pacman::~Pacman()
{
}

int randPos()
{
    return std::rand() % 4 + 1;
}

int inc(int var)
{
    static clock_t timer = 0;

    if ((clock() - timer) > 1000000)
        var++;
    return (var);
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

std::list<std::shared_ptr<PacObject>> Pacman::initGame(void)
{
    std::list<std::shared_ptr<PacObject>> tmpList;
    std::list<std::shared_ptr<PacObject>> list;
    std::shared_ptr<PacObject> ptr;
    std::string line;
    std::ifstream myfile ("./games/pacman/map.txt");

    if (!myfile.is_open())
        throw(std::string("Could not open Pacman map"));
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
        _maze.push_back(line);
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

    usleep(100000);
    //_timerPath = inc(_timerPath);
    moveGhost(obj);
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
            if (type == PacObject::STAR) {
                *it = createObject(pos.first, pos.second, ' ');
                break;
            }
            if (type == PacObject::GOLD) {
                *it = createObject(pos.first, pos.second, ' ');
                _pacgum = true;
                break;
            }
        }
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
    _pacPos = pos;
    return (0);
}




//GHOST

void Pacman::setPath(int gh)
{
    std::vector<std::pair<float, float>> tmp;
    std::pair<float, float> curPos;
    std::pair<float, float> dest;

    std::cout << "fuck" << std::endl;
    curPos.first = _curPos[gh].first / 32;
    curPos.second = _curPos[gh].second / 32;
    if (_isJail[gh] == false) {
        dest.first = _pacPos.first / 32;
        dest.second = _pacPos.second / 32;
    }
    else {
        dest = std::pair<float, float>(11, 12);
    }
    std::cout << "before" << std::endl;
    Backtrack g(curPos, _maze, dest);
    std::cout << "after" << std::endl;
    tmp = g.getPath();
    _curPos[gh] = tmp[0];
    _ghostPath[gh] = tmp;
}

void Pacman::isNewGhostPath()
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == false)
            setPath(gh);
    }
}

void Pacman::setGhostAnim(int gh)
{
    if (_isJail[gh])
        return;
    if (_curPos[gh].first < _ghostPath[gh][0].first)
        pacRects[gh+3] = leftAnim[gh];
    if (_curPos[gh].first > _ghostPath[gh][0].first)
        pacRects[gh+3] = rightAnim[gh];
    if (_curPos[gh].second < _ghostPath[gh][0].second)
        pacRects[gh+3] = downAnim[gh];
    if (_curPos[gh].second > _ghostPath[gh][0].second)
        pacRects[gh+3] = upAnim[gh];
}

void Pacman::setGhostPos(std::list<std::shared_ptr<PacObject>> obj)
{
    std::pair<float, float> newPos;
    std::shared_ptr<PacObject> tmp;
    size_t gh = 0;

    for (auto it = obj.begin(); gh != 4; ++it) {
        tmp = *it;
        if (_isJail[gh] == true && inJail(gh))
            newPos = randMoveJail(*it);
        else {
            setGhostAnim(gh);
            newPos = _ghostPath[gh][0];
            _ghostPath[gh].erase(_ghostPath[gh].begin());
        }
        tmp->setPos(newPos);
        _curPos[gh] = newPos;
        gh++;
    }
}

bool Pacman::ghColisionPac(int gh)
{
    if (_curPos[gh].first == _pacPos.first
    && _curPos[gh].second == _pacPos.second)
        return true;
    return false;
}

void Pacman::isGhMeetPac()
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == true)
            continue;
        if (_pacgum == false && ghColisionPac(gh)) {
            _lost = true;
            return;
        }
        else if (_pacgum == true && ghColisionPac(gh)) {
            _isJail[gh] = true;
            pacRects[gh+3] = deadAnim[0];
            setPath(gh);
        }
    }
}

/* void jailPath()
{

} */
//x 9 et 12 y 12 et 13
bool Pacman::inJail(int gh)
{
    if (_curPos[gh].second >= 12 * 32 && _curPos[gh].second <= 13 * 32
    && _curPos[gh].first >= 9 * 32 && _curPos[gh].first <= 12 * 32)
        return true;
    return false;
}

bool Pacman::checkColisionJail(std::pair<float, float> pos)
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

std::pair<float, float> Pacman::randMoveJail(std::shared_ptr<PacObject> obj)
{
    int dir = randPos();
    std::pair<float, float> pos;

    if (dir == 1)
        pos = std::pair<float, float>(obj->getPos().first - 32.0, obj->getPos().second);
    if (dir == 2)
        pos = std::pair<float, float>(obj->getPos().first + 32.0, obj->getPos().second);
    if (dir == 3)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second - 32.0);
    if (dir == 4)
        pos = std::pair<float, float>(obj->getPos().first, obj->getPos().second + 32.0);
    if (checkColisionJail(pos))
        return randMoveJail(obj);
    else
        return pos;
}

void Pacman::jailGhost()
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == true && inJail(gh)) {
            return;
        }
    }
}

void Pacman::checkTimers()
{
/*     if (_timerPath >= 3) {
        std::cout << _timerPath << std::endl;
        _timerPath = 0;
    }
    for (size_t i = 0; i != 4; i++) {
        if (_timerJail[gh] >= 10) {
            _timerJail[gh] = 0;
            _isJail[gh] = false;
            setPath(gh);
        }
    } */
}

void Pacman::moveGhost(std::list<std::shared_ptr<PacObject>> obj)
{
    static bool enc = true;
/*     std::cout << _timerPath << std::endl; */
    /* if (_timerPath >= 3) */
    if (enc) {
        isNewGhostPath();           //get Path
        enc = false;
    }
    setGhostPos(obj);           //set Path
    isGhMeetPac();              //checkJail
    jailGhost();                //behavior in jail
    /* checkTimers();            //restar clock */
}


//FIN GHOST



char Pacman::getAppearanceCharIdx(int idx)
{
    return pacFlags[idx];
}

Rect Pacman::getAppearanceRectIdx(int idx)
{
    return pacRects[idx];
}