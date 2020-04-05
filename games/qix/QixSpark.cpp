/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixSpark
*/

#include "QixSpark.hpp"

QixSpark::QixSpark(float posx, float posy, int basedirection)
{
    appearance = type = SPARK;
    pos = {posx, posy};
    timer_move = 20;
    direction = basedirection;
}

QixSpark::~QixSpark()
{

}

std::pair<float, float> QixSpark::getPos() const
{
    return pos;
}

char QixSpark::getAppearance() const
{
    return appearance;
}

char QixSpark::getType() const
{
    return type;
}

void QixSpark::setPos(float posx, float posy)
{
    pos = {posx, posy};
}

void QixSpark::setPos(std::pair<float, float> newpos)
{
    pos = newpos;
}

void QixSpark::setDirection(int direction)
{
    this->direction = direction;
}

std::pair<float, float> QixSpark::getObjectivePos(int direction) const
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

int QixSpark::check_can_move_border(std::list<std::shared_ptr<QixGround>> tiles, std::pair<float, float> objectivePos)
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
        || (tilePos.first == (objectivePos.first - 16) && tilePos.second == (objectivePos.second - 16))))
            return 1;
    }
    return 0;
}

int QixSpark::check_can_move(std::list<std::shared_ptr<QixGround>> tiles, int direction)
{
    std::pair<float, float> objectivePos = getObjectivePos(direction);
    std::pair<float, float> tilePos;

    if (pos == objectivePos)
        return 0;
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        tilePos = (*it)->getPos();
        if (tilePos == objectivePos && ((*it)->getType() == QixGround::FULL || (*it)->getType() == QixGround::EMPTY))
            return 0;
        if (tilePos == objectivePos && (*it)->getType() == QixGround::BORDER)
            return check_can_move_border(tiles, objectivePos);
    }
    return 0;
}

int QixSpark::check_can_move_blocked(std::list<std::shared_ptr<QixGround>> tiles, int direction)
{
    std::pair<float, float> objectivePos = getObjectivePos(direction);

    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getPos() == objectivePos && (*it)->getType() == QixGround::BORDER)
            return 1;
    }
    return 0;
}

void QixSpark::move(std::list<std::shared_ptr<QixGround>> tiles)
{
    int basedirection = direction;

    timer_move++;
    if (timer_move < 18)
        return;
    timer_move = 0;
    if (check_can_move(tiles, direction)) {
        pos = getObjectivePos(direction);
        return;
    }
    if (direction == 1 || direction == 2) {
        direction = 3;
        if (check_can_move(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
        direction = 4;
        if (check_can_move(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
    }
    else {
        direction = 1;
        if (check_can_move(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
        direction = 2;
        if (check_can_move(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
    }
    direction = basedirection;
    if (check_can_move_blocked(tiles, direction)) {
        pos = getObjectivePos(direction);
        return;
    }
    if (direction == 1 || direction == 2) {
        direction = 3;
        if (check_can_move_blocked(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
        direction = 4;
        if (check_can_move_blocked(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
    }
    else {
        direction = 1;
        if (check_can_move_blocked(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
        direction = 2;
        if (check_can_move_blocked(tiles, direction)) {
            pos = getObjectivePos(direction);
            return;
        }
    }
}