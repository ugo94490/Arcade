/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** PacObject
*/

#pragma once

#include "IGameObject.hpp"

class MenuObject : public IGameObject {
    public:
        enum objtypes {
            M,
            E,
            N,
            U,
            I,
            B,
            L,
            R,
            P,
            A,
            C,
            Q,
            X,
            S,
            O,
            K,
            T,
            BARRE,
            TILT,
            F,
            D,
            SPACE,
        };
        MenuObject(float posx, float posy, char c);
        ~MenuObject();
        std::pair<float, float> getPos() const;
        void setPos(std::pair<float, float> pos);
        char getAppearance() const;
        char getType() const;
        void setType();

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
};