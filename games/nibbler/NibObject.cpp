/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NibObject
*/

#include <iostream>
#include "NibObject.hpp"

NibObject::NibObject(float posx, float posy, char c)
{
    pos = std::pair<float, float>(posx, posy);
    c == 'P' ? type = PLAYER : 0;
    c == '#' ? type = WALL : 0;
    c == ' ' ? type = FLOOR : 0;
    c == 'x' ? type = STAR : 0;
    c == 'T' ? type = TAIL : 0;
    appearance = type;
}

NibObject::~NibObject()
{
}

char NibObject::getAppearance(void) const
{
    return appearance;
}

char NibObject::getType(void) const
{
    return type;
}

std::pair<float, float> NibObject::getPos(void) const
{
    return pos;
}

void NibObject::setPos(std::pair<float, float> pos)
{
    this->pos = pos;
}

void NibObject::setType(char c)
{
    type = c;
}

void NibObject::setAppearance(char c)
{
    appearance = c;
}