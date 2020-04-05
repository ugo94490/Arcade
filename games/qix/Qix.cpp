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

static const Rect qixRects[6] = {
    {0, 0, 32, 32},
    {32, 0, 32, 32},
    {64, 0, 32, 32},
    {96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32}
};

static std::string qixChars = " .XO*=";

Qix::Qix()
{
    score = 0;
    initGame();
}

void Qix::initGame(void)
{
    sparks.clear();
    tiles.clear();
    tiles = initMap();
    player = initPlayer();
    qix = std::shared_ptr<QixQix>(new QixQix(320, 320));
    sparks.push_back(std::shared_ptr<QixSpark>(new QixSpark(304, 0, 1)));
    sparks.push_back(std::shared_ptr<QixSpark>(new QixSpark(336, 0, 2)));
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
    std::list<std::shared_ptr<QixQixNode>> qixnodes = qix->getNodes();

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        list.push_back(*it);
    }
    for (auto it = playerTrail.begin(); it != playerTrail.end(); ++it)
        list.push_back(*it);
    for (auto it = qixnodes.begin(); it != qixnodes.end(); ++it)
        list.push_back(*it);
    for (auto it = sparks.begin(); it != sparks.end(); ++it)
        list.push_back(*it);
    list.push_back(player);
    return (list);
}

int Qix::handleEvents(const unsigned char &c)
{
    if (!player)
        throw(Exception ("Player does not exist"));
    if (c <= 4)
        player->setDirection(c);
    if (checkWin() == 1)
        return 1;
    if (player->getAlive() == 0)
        return 1;
    return (0);
}

void Qix::updateGame(void)
{
    int scoreadded = 0;

    player->check_can_move(tiles);
    player->move_direction(tiles);
    scoreadded = player->try_close_trail(tiles, qix);
    score += scoreadded;
    qix->move(tiles);
    for (auto it = sparks.begin(); it != sparks.end(); ++it)
        (*it)->move(tiles);
    player->check_collision_qix(qix);
    player->check_collision_sparks(sparks);
    score += 2;
}

char Qix::getAppearanceCharIdx(int idx)
{
    if ((std::size_t)(idx) > qixChars.length() || idx < 0)
        return ' ';
    return qixChars[idx];
}

Rect Qix::getAppearanceRectIdx(int idx)
{
    if ((std::size_t)(idx) > qixChars.length() || idx < 0)
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
        throw(Exception ("Could not open Qix map"));
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

int Qix::checkWin(void) const
{
    int nb_to_win = 1364;
    int nb_ok = 0;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getType() == QixGround::BORDER || (*it)->getType() == QixGround::FULL)
            nb_ok++;
    }
    if (nb_ok >= nb_to_win)
        return (1);
    return (0);
}