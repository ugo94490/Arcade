/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NibObject
*/

#pragma once

#include "IGameObject.hpp"

class NibObject : public IGameObject {
    public:
        enum objtypes {
            PLAYER = 0,
            WALL,
            STAR,
            FLOOR,
            TAIL
        };
        NibObject(float posx, float posy, char c);
        ~NibObject();
        std::pair<float, float> getPos() const;
        void setPos(std::pair<float, float> pos);
        char getAppearance() const;
        char getType() const;
        void setType(char);
        void setAppearance(char);

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};
