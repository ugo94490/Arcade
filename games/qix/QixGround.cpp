/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixGround
*/

#include "QixGround.hpp"

QixGround::QixGround(float posx, float posy, char c)
{
    type = EMPTY;
    if (c == '.')
        type = BORDER;
    appearance = type;
    pos = {posx, posy};
}

QixGround::~QixGround()
{

}

std::pair<float, float> QixGround::getPos() const
{
    return pos;
}

char QixGround::getAppearance() const
{
    return appearance;
}

char QixGround::getType() const
{
    return type;
}