/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixQixNode
*/

#include "QixQixNode.hpp"

QixQixNode::QixQixNode(float posx, float posy)
{
    appearance = type = QIX;
    pos = {posx, posy};
}

QixQixNode::~QixQixNode()
{

}

std::pair<float, float> QixQixNode::getPos() const
{
    return pos;
}

char QixQixNode::getAppearance() const
{
    return appearance;
}

char QixQixNode::getType() const
{
    return type;
}

void QixQixNode::setPos(float posx, float posy)
{
    pos = {posx, posy};
}

void QixQixNode::setPos(std::pair<float, float> newpos)
{
    pos = newpos;
}

void QixQixNode::setDirection(int direction)
{
    this->direction = direction;
}

std::pair<float, float> QixQixNode::getObjectivePos() const
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

int QixQixNode::check_can_move(std::list<std::shared_ptr<QixGround>> tiles)
{
    std::pair<float, float> objectivePos = getObjectivePos();
    std::pair<float, float> tilePos;

    if (pos == objectivePos) {
        direction = 0;
        return 0;
    }
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        tilePos = (*it)->getPos();
        if (tilePos == objectivePos && (*it)->getType() == QixGround::EMPTY) {
            objective = tilePos;
            return 1;
        }
        else if (tilePos == objectivePos) {
            direction = 0;
            objective = pos;
            return 0;
        }
    }
    return 0;
}

char QixQixNode::check_type_on_pos(std::pair<float, float> poscheck, std::list<std::shared_ptr<QixGround>> tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->getPos() == poscheck)
            return ((*it)->getType());
    }
    return -1;
}

void QixQixNode::move_direction(void)
{
    if (direction == 0)
        return;
    pos = objective;
}