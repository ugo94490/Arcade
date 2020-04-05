/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixGround
*/

#pragma once

#include "IGameObject.hpp"

class QixGround : public IGameObject {
    public:
        enum objtypes {
            EMPTY = 0,
            BORDER,
            FULL
        };
        QixGround(float posx, float posy, char c);
        ~QixGround();
        std::pair<float, float> getPos() const;
        char getAppearance() const;
        char getType() const;
        void changeType(char newtype);

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};