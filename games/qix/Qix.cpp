/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Qix
*/

#include <fstream>
#include <string>
#include "Qix.hpp"

using namespace std;

static const int BLOCK_SIZE = 16;

static const Rect qixRects[4] = {
    {0, 0, 16, 16},
    {16, 0, 16, 16},
    {32, 0, 16, 16},
    {48, 0, 16, 16}
};

static std::string qixChars = " .XO*=";

Qix::Qix()
{
    tiles = initMap();
    player = initPlayer();
    score = 0;
}

Qix::~Qix()
{
}

int Qix::getScore() const
{
    return (score);
}

std::list<std::shared_ptr<IGameObject>> Qix::getObjects(void) const
{
    std::list<std::shared_ptr<IGameObject>> list;
    std::list<std::shared_ptr<QixTrail>> playerTrail = player->getTrail();

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        list.push_back(*it);
    }
    for (auto it = playerTrail.begin(); it != playerTrail.end(); ++it)
        list.push_back(*it);
    list.push_back(player);
    return (list);
}

int Qix::handleEvents(const unsigned char &c)
{
    if (!player)
        throw("Player does not exist");
    if (c >= 0 && c <= 4)
        player->setDirection(c);
    return (0);
}

void Qix::updateGame(void)
{
    player->check_can_move(tiles);
    player->move_direction(tiles);
}

char Qix::getAppearanceCharIdx(int idx)
{
    if (idx > qixChars.length() || idx < 0)
        return ' ';
    return qixChars[idx];
}

Rect Qix::getAppearanceRectIdx(int idx)
{
    if (idx > qixChars.length() || idx < 0)
        return {0, 0, 0, 0};
    return qixRects[idx];
}

std::list<std::shared_ptr<QixGround>> Qix::initMap(void) const
{
    std::list<std::shared_ptr<QixGround>> list;
    std::shared_ptr<QixGround> ptr;
    string line;
    ifstream myfile ("./games/qix/map.txt");

    if (!myfile.is_open())
        throw(std::string("Could not open Qix map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        for (int j = 0; line[j]; j++) {
            ptr = createTile(j * BLOCK_SIZE, i * BLOCK_SIZE, line[j]);
            if (ptr)
                list.push_front(ptr);
        }
    }
    myfile.close();
    return list;
}

std::shared_ptr<QixPlayer> Qix::initPlayer(void) const
{
    std::shared_ptr<QixPlayer> ptr(new QixPlayer(BLOCK_SIZE * 20, BLOCK_SIZE * 41));
    return ptr;
}

std::shared_ptr<QixGround> Qix::createTile(float posx, float posy, char c) const
{
    if (c != '.' && c != ' ')
        return NULL;
    std::shared_ptr<QixGround> ptr(new QixGround(posx, posy, c));
    return (ptr);
}

int Qix::getBlockSize() const
{
    return BLOCK_SIZE;
}