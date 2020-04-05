/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixQix
*/

#pragma once

#include "QixQixNode.hpp"

class QixQix {
    public:
        QixQix(float posx, float posy);
        ~QixQix();
        void setPos(float posx, float posy);
        int check_can_move(std::list<std::shared_ptr<QixGround>> tiles);
        void move(std::list<std::shared_ptr<QixGround>> tiles);
        std::list<std::shared_ptr<QixQixNode>> getNodes(void) const;

    private:
        std::list<std::shared_ptr<QixQixNode>> nodes;
        int timer_move;
};