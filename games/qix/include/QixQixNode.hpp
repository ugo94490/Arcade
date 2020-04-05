/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixQixNode
*/

#pragma once

#include "QixGround.hpp"
#include <memory>
#include <list>

class QixQixNode : public IGameObject {
    public:
        enum objtypes {
            QIX = 5
        };
        QixQixNode(float posx, float posy);
        ~QixQixNode();
        std::pair<float, float> getPos() const;
        char getAppearance() const;
        char getType() const;
        void setPos(float posx, float posy);
        void setPos(std::pair<float, float> newpos);
        void setDirection(int direction);
        int check_can_move(std::list<std::shared_ptr<QixGround>> tiles);
        void move_direction(void);
        std::pair<float, float> getObjectivePos() const;
        static char check_type_on_pos(std::pair<float, float> poscheck, std::list<std::shared_ptr<QixGround>> tiles);

    private:
        std::pair<float, float> pos;
        std::pair<float, float> objective;
        char appearance;
        char type;
        int direction;
};