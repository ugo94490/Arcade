/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** PacObject
*/

#pragma once

#include "IGameObject.hpp"

class PacObject : public IGameObject {
    public:
        enum objtypes {
            PLAYER = 0,
            WALL,
            GDOOR,
            RED,
            BLUE,
            ORANGE,
            YELLOW,
            STAR,
            GOLD,
            SPACE,
        };
        size_t star = 188;
        PacObject(float posx, float posy, char c);
        ~PacObject();
        std::pair<float, float> getPos() const;
        void setPos(std::pair<float, float> pos);
        char getAppearance() const;
        char getType() const;
        void setType();
        void setStar();
        size_t getStar() const;

    private:
        /* size_t star = 188; */
        std::pair<float, float> pos;
        char appearance;
        char type;
};