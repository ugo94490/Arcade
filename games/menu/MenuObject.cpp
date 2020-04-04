/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** MenuObject
*/

#include <iostream>
#include "MenuObject.hpp"

MenuObject::MenuObject(float posx, float posy, char c)
{
    pos = std::pair<float, float>(posx, posy);
    c == 'M' ? type = M : 0;
    c == 'E' ? type = E : 0;
    c == 'N' ? type = N : 0;
    c == 'U' ? type = U : 0;
    c == 'I' ? type = I : 0;
    c == 'B' ? type = B : 0;
    c == 'L' ? type = L : 0;
    c == 'R' ? type = R : 0;
    c == 'P' ? type = P : 0;
    c == 'A' ? type = A : 0;
    c == 'C' ? type = C : 0;
    c == 'Q' ? type = Q : 0;
    c == 'X' ? type = X : 0;
    c == 'S' ? type = S : 0;
    c == 'O' ? type = O : 0;
    c == 'K' ? type = K : 0;
    c == 'T' ? type = T : 0;
    c == '-' ? type = BARRE : 0;
    c == '|' ? type = TILT : 0;
    c == 'F' ? type = F : 0;
    c == 'D' ? type = D : 0;
    c == ' ' ? type = SPACE : 0;
    appearance = type;
}

MenuObject::~MenuObject()
{
}

char MenuObject::getAppearance(void) const
{
    return appearance;
}

char MenuObject::getType(void) const
{
    return type;
}

std::pair<float, float> MenuObject::getPos(void) const
{
    return pos;
}

void MenuObject::setType()
{
    this->type = ' ';
}

void MenuObject::setPos(std::pair<float, float> pos)
{
    this->pos = pos;
}