/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SokoObject
*/

#pragma once

#include "IGameObject.hpp"

class SokoObject : public IGameObject {
    public:
        enum objtypes {
            PLAYER = 0,
            CRATE,
            DEST,
            WALL
        };
        SokoObject(float posx, float posy, char c);
        ~SokoObject();
        std::pair<float, float> getPos() const;
        void setPos(std::pair<float, float> pos);
        char getAppearance() const;
        char getType() const;

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};