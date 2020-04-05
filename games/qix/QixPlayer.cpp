/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixPlayer
*/

#include "QixPlayer.hpp"

QixPlayer::QixPlayer(float posx, float posy)
{
    appearance = type = PLAYER;
    pos = {posx, posy};
    timer_move = 20;
    timer_burn = 0;
    alive = 1;
}

QixPlayer::~QixPlayer()
{

}

std::pair<float, float> QixPlayer::getPos() const
{
    return pos;
}

char QixPlayer::getAppearance() const
{
    return appearance;
}

char QixPlayer::getType() const
{
    return type;
}

void QixPlayer::setPos(float posx, float posy)
{
    pos = {posx, posy};
}

void QixPlayer::setPos(std::pair<float, float> newpos)
{
    pos = newpos;
}

void QixPlayer::setDirection(int direction)
{
    this->direction = direction;
}

std::pair<float, float> QixPlayer::getObjectivePos() const
{
    if (direction == 1)
        return {pos.first - 16, pos.second};
    if (direction == 2)
        return {pos.first + 16, pos.second};
    if (direction == 3)
        return {pos.first, pos.second - 16};
    if (direction == 4)
        return {pos.first, pos.second + 16};
    return pos;
}

void QixPlayer::check_can_move_border(std::list<std::shared_ptr<QixGround>> const &tiles,
std::pair<float, float> const &objectivePos)
{
    std::pair<float, float> tilePos;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        tilePos = (*it)->getPos();
        if ((*it)->getType() == QixGround::EMPTY &&
        ((tilePos.first == objectivePos.first && tilePos.second == (objectivePos.second + 16))
        || (tilePos.first == objectivePos.first && tilePos.second == (objectivePos.second - 16))
        || (tilePos.first == (objectivePos.first + 16) && tilePos.second == objectivePos.second)
        || (tilePos.first == (objectivePos.first - 16) && tilePos.second == objectivePos.second)
        || (tilePos.first == (objectivePos.first + 16) && tilePos.second == (objectivePos.second + 16))
        || (tilePos.first == (objectivePos.first - 16) && tilePos.second == (objectivePos.second + 16))
        || (tilePos.first == (objectivePos.first + 16) && tilePos.second == (objectivePos.second - 16))
        || (tilePos.first == (objectivePos.first - 16) && tilePos.second == (objectivePos.second - 16)))) {
            objective = objectivePos;
            return;
        }
    }
    objective = this->pos;
    direction = 0;
    return;
}

void QixPlayer::check_can_move(std::list<std::shared_ptr<QixGround>> const &tiles)
{
    std::pair<float, float> objectivePos = getObjectivePos();
    std::pair<float, float> tilePos;

    if (pos == objectivePos) {
        direction = 0;
        return;
    }
    for (auto it = trail.begin(); it != trail.end(); ++it) {
        if ((*it)->getPos() == objectivePos) {
            direction = 0;
            return;
        }
    }
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        tilePos = (*it)->getPos();
        if (tilePos == objectivePos && (*it)->getType() == QixGround::FULL) {
            direction = 0;
            return;
        }
        if (tilePos == objectivePos && (*it)->getType() == QixGround::EMPTY) {
            objective = tilePos;
            return;
        }
        if (tilePos == objectivePos && (*it)->getType() == QixGround::BORDER) {
            check_can_move_border(tiles, objectivePos);
            return;
        }
    }
}

char QixPlayer::check_type_on_pos(std::pair<float, float> const &poscheck, std::list<std::shared_ptr<QixGround>> const &tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getPos() == poscheck)
            return ((*it)->getType());
    }
    return -1;
}

void QixPlayer::move_direction(std::list<std::shared_ptr<QixGround>> const &tiles)
{
    timer_move++;
    if (direction == 0 && timer_move > 15)
        burnTrail();
    if (direction == 0 || timer_move < 15)
        return;
    if (check_type_on_pos(objective, tiles) == QixGround::EMPTY || check_type_on_pos(pos, tiles) == QixGround::EMPTY)
        trail.push_back(std::shared_ptr<QixTrail>(new QixTrail(pos.first, pos.second)));
    if (check_type_on_pos(objective, tiles) == QixGround::BORDER && check_type_on_pos(pos, tiles) == QixGround::EMPTY)
        trail.push_back(std::shared_ptr<QixTrail>(new QixTrail(objective.first, objective.second)));
    pos = objective;
    timer_move = 0;
}

void QixPlayer::burnTrail(void)
{
    auto it = trail.begin();
    timer_burn++;
    if (timer_burn < 30 || it == trail.end())
        return;
    for (; it != trail.end(); ++it)
        if ((*it)->getType() == QixTrail::TRAIL)
            break;
    if (it == trail.end()) {
        alive = 0;
        return;
    }
    (*it)->setType(QixTrail::BURNT);
    timer_burn = 0;
}

int QixPlayer::getAlive(void) const
{
    return alive;
}

std::list<std::shared_ptr<QixTrail>> QixPlayer::getTrail() const
{
    return trail;
}

void QixPlayer::check_collision_qix(std::shared_ptr<QixQix> const &qix)
{
    std::list<std::shared_ptr<QixQixNode>> qixnodes = qix->getNodes();
    std::pair<float, float> trailPos;
    std::pair<float, float> nodePos;

    for (auto it = trail.begin(); it != trail.end(); ++it) {
        trailPos = (*it)->getPos();
        for (auto it2 = qixnodes.begin(); it2 != qixnodes.end(); ++it2) {
            nodePos = (*it2)->getPos();
            if (trailPos == nodePos || pos == nodePos) {
                alive = 0;
                return;
            }
        }
    }
}

void QixPlayer::check_collision_sparks(std::list<std::shared_ptr<QixSpark>> const &sparks)
{
    for (auto it = sparks.begin(); it != sparks.end(); ++it) {
        if (pos == (*it)->getPos()) {
            alive = 0;
            return;
        }
    }
}


std::pair<float, float> QixPlayer::getPosDirection(std::pair<float, float> basepos, int direction)
{
    if (direction == 1)
        return {basepos.first - 16, basepos.second};
    if (direction == 2)
        return {basepos.first + 16, basepos.second};
    if (direction == 3)
        return {basepos.first, basepos.second - 16};
    if (direction == 4)
        return {basepos.first, basepos.second + 16};
    return basepos;
}

std::shared_ptr<QixGround> QixPlayer::getGroundOnPos(std::pair<float, float> pos, std::list<std::shared_ptr<QixGround>> tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getPos() == pos)
            return (*it);
    }
    return NULL;
}

std::list<std::shared_ptr<QixGround>> QixPlayer::getzone(std::list<std::shared_ptr<QixGround>> tiles)
{
    std::list<std::shared_ptr<QixGround>> zone;
    std::shared_ptr<QixGround> tempground;
    int found = 1;
    int direction = 0;
    std::pair<float, float> tempObjective;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getType() == QixGround::EMPTY) {
            (*it)->changeType(QixGround::FULL);
            zone.push_back(*it);
            break;
        }
    }
    while (found == 1)
    {
        found = 0;
        for (auto it = zone.begin(); it != zone.end(); ++it) {
            direction = 1;
            tempground = getGroundOnPos(getPosDirection((*it)->getPos(), direction), tiles);
            if (tempground->getType() == QixGround::EMPTY) {
                tempground->changeType(QixGround::FULL);
                zone.push_back(tempground);
                found = 1;
            }
            direction = 2;
            tempground = getGroundOnPos(getPosDirection((*it)->getPos(), direction), tiles);
            if (tempground->getType() == QixGround::EMPTY) {
                tempground->changeType(QixGround::FULL);
                zone.push_back(tempground);
                found = 1;
            }
            direction = 3;
            tempground = getGroundOnPos(getPosDirection((*it)->getPos(), direction), tiles);
            if (tempground->getType() == QixGround::EMPTY) {
                tempground->changeType(QixGround::FULL);
                zone.push_back(tempground);
                found = 1;
            }
            direction = 4;
            tempground = getGroundOnPos(getPosDirection((*it)->getPos(), direction), tiles);
            if (tempground->getType() == QixGround::EMPTY) {
                tempground->changeType(QixGround::FULL);
                zone.push_back(tempground);
                found = 1;
            }
        }
    }
    return zone;
}

int QixPlayer::check_qix_here(std::list<std::shared_ptr<QixGround>> const &zone, std::shared_ptr<QixQix> const &qix)
{
    std::list<std::shared_ptr<QixQixNode>> qixnodes = qix->getNodes();
    std::pair<float, float> tilePos;

    for (auto it = zone.begin(); it != zone.end(); ++it) {
        tilePos = (*it)->getPos();
        for (auto it2 = qixnodes.begin(); it2 != qixnodes.end(); ++it2) {
            if ((*it2)->getPos() == tilePos)
                return (1);
        }
    }
    return (0);
}

int QixPlayer::close_trail(std::list<std::shared_ptr<QixGround>> &tiles, std::shared_ptr<QixQix> const &qix)
{
    std::list<std::shared_ptr<QixGround>> zone;
    std::pair<float, float> trailPos;
    int score_ret = 0;
    
    for (auto it = trail.begin(); it != trail.end(); ++it) {
        trailPos = (*it)->getPos();
        for (auto it2 = tiles.begin(); it2 != tiles.end(); ++it2) {
            if ((*it2)->getPos() == trailPos && (*it2)->getType() == QixGround::EMPTY) {
                (*it2)->changeType(QixGround::BORDER);
                score_ret += 2000;
            }
        }
    }
    zone = getzone(tiles);
    if (check_qix_here(zone, qix) == 1) {
        for (auto it = tiles.begin(); it != tiles.end(); ++it) {
            if ((*it)->getType() == QixGround::EMPTY) {
                (*it)->changeType(QixGround::FULL);
                score_ret += 2000;
            }
        }
        for (auto it = zone.begin(); it != zone.end(); ++it)
            (*it)->changeType(QixGround::EMPTY);
    }
    else
        for (auto it = zone.begin(); it != zone.end(); ++it)
            score_ret += 2000;
    return score_ret;
}

int QixPlayer::try_close_trail(std::list<std::shared_ptr<QixGround>> &tiles, std::shared_ptr<QixQix> const &qix)
{
    auto it = trail.end();
    int score_ret = 0;

    if (trail.begin() == trail.end())
        return 0;
    --it;
    if (it == trail.begin())
        return 0;
    if (check_type_on_pos((*it)->getPos(), tiles) == QixGround::BORDER) {
        score_ret = close_trail(tiles, qix);
        trail.clear();
    }
    return score_ret;
}