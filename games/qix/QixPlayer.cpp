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

void QixPlayer::check_can_move_border(std::list<std::shared_ptr<QixGround>> tiles, std::pair<float, float> objectivePos)
{
    std::pair<float, float> tilePos;

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        tilePos = (*it)->getPos();
        if ((*it)->getType() == QixGround::EMPTY && tilePos.first == objectivePos.first && tilePos.second == (objectivePos.second + 16)) {
            objective = objectivePos;
            return;
        }
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

void QixPlayer::check_can_move(std::list<std::shared_ptr<QixGround>> tiles)
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

char QixPlayer::check_type_on_pos(std::pair<float, float> poscheck, std::list<std::shared_ptr<QixGround>> tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getPos() == poscheck)
            return ((*it)->getType());
    }
    return -1;
}

void QixPlayer::move_direction(std::list<std::shared_ptr<QixGround>> tiles)
{
    timer_move++;
    if (direction == 0 && timer_move > 20)
        burnTrail();
    if (direction == 0 || timer_move < 20)
        return;
    if (check_type_on_pos(objective, tiles) == QixGround::EMPTY || check_type_on_pos(pos, tiles) == QixGround::EMPTY)
        trail.push_back(std::shared_ptr<QixTrail>(new QixTrail(pos.first, pos.second)));
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

void QixPlayer::check_collision_qix(std::shared_ptr<QixQix> qix)
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