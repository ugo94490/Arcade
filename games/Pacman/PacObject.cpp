/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** PacObject
*/

#include <iostream>
#include "PacObject.hpp"

PacObject::PacObject(float posx, float posy, char c)
{
    pos = std::pair<float, float>(posx, posy);
    c == '0' ? type = PLAYER : 0;
    c == '1' ? type = CRATE : 0;
    c == '2' ? type = DEST : 0;
    appearance = type;
}

PacObject::~PacObject()
{
}

char PacObject::getAppearance(void) const
{
    return appearance;
}

char PacObject::getType(void) const
{
    return type;
}

std::pair<float, float> PacObject::getPos(void) const
{
    return pos;
}

void PacObject::setPos(std::pair<float, float> pos)
{
    this->pos = pos;
}