/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixTrail
*/

#pragma once

#include "IGameObject.hpp"

class QixTrail : public IGameObject {
    public:
        enum objtypes {
            TRAIL = 4,
            BURNT
        };
        QixTrail(float posx, float posy);
        ~QixTrail();
        std::pair<float, float> getPos() const;
        char getAppearance() const;
        char getType() const;
        void setType(char type);

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};