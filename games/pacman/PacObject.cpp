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
    c == 'P' ? type = PLAYER : 0;
    c == 'X' ? type = WALL : 0;
    c == '*' ? type = STAR : 0;
    c == 'O' ? type = DOOR : 0;
    c == 'Q' ? type = GDOOR : 0;
    c == ' ' ? type = SPACE : 0;
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

void PacObject::setType()
{
    this->type = ' ';
}

void PacObject::setPos(std::pair<float, float> pos)
{
    this->pos = pos;
}