/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixSpark
*/

#pragma once

#include "QixGround.hpp"
#include <memory>
#include <list>

class QixSpark : public IGameObject {
    public:
        enum objtypes {
            SPARK = 4
        };
        QixSpark(float posx, float posy, int basedirection);
        ~QixSpark();
        std::pair<float, float> getPos() const;
        char getAppearance() const;
        char getType() const;
        void setPos(float posx, float posy);
        void setPos(std::pair<float, float> newpos);
        void setDirection(int direction);
        int check_can_move(std::list<std::shared_ptr<QixGround>> tiles, int direction);
        int check_can_move_border(std::list<std::shared_ptr<QixGround>> tiles, std::pair<float, float> pos);
        int check_can_move_blocked(std::list<std::shared_ptr<QixGround>> tiles, int direction);
        void move(std::list<std::shared_ptr<QixGround>> tiles);
        std::pair<float, float> getObjectivePos(int direction) const;
        static char check_type_on_pos(std::pair<float, float> poscheck, std::list<std::shared_ptr<QixGround>> tiles);

    private:
        std::pair<float, float> pos;
        char appearance;
        char type;
        int direction;
        int timer_move;
};