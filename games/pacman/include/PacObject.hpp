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
            PLAYER,
            WALL,
            STAR,
            DOOR,
            GDOOR,
            SPACE,
        };
        PacObject(float posx, float posy, char c);
        ~PacObject();
        std::pair<float, float> getPos() const;
        void setPos(std::pair<float, float> pos);
        void setType(char newType);
        char getAppearance() const;
        char getType() const;

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};