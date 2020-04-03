/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixTrail
*/

#include "QixTrail.hpp"

QixTrail::QixTrail(float posx, float posy)
{
    type = TRAIL;
    appearance = 1;
    pos = {posx, posy};
}

QixTrail::~QixTrail()
{

}

std::pair<float, float> QixTrail::getPos() const
{
    return pos;
}

char QixTrail::getAppearance() const
{
    return appearance;
}

char QixTrail::getType() const
{
    return type;
}

void QixTrail::setType(char type)
{
    this->type = type;
    if (type == BURNT)
        appearance = 4;
    else
        appearance = 1;
}