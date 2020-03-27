/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SokoObject
*/

#include <iostream>
#include "SokoObject.hpp"

SokoObject::SokoObject(float posx, float posy, char c)
{
    pos = std::pair<float, float>(posx, posy);
    c == 'P' ? type = PLAYER : 0;
    c == 'X' ? type = CRATE : 0;
    c == 'O' ? type = DEST : 0;
    c == '#' ? type = WALL : 0;
    appearance = type;
}

SokoObject::~SokoObject()
{
}

char SokoObject::getAppearance(void) const
{
    return appearance;
}

char SokoObject::getType(void) const
{
    return type;
}

std::pair<float, float> SokoObject::getPos(void) const
{
    return pos;
}

void SokoObject::setPos(std::pair<float, float> pos)
{
    this->pos = pos;
}