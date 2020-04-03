/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixPlayer
*/

#pragma once

#include "IGameObject.hpp"
#include "QixGround.hpp"
#include "QixTrail.hpp"
#include <memory>
#include <list>

class QixPlayer : public IGameObject {
    public:
        enum objtypes {
            PLAYER = 3
        };
        QixPlayer(float posx, float posy);
        ~QixPlayer();
        std::pair<float, float> getPos() const;
        char getAppearance() const;
        char getType() const;
        void setPos(float posx, float posy);
        void setPos(std::pair<float, float> newpos);
        void setDirection(int direction);
        void check_can_move(std::list<std::shared_ptr<QixGround>>);
        void check_can_move_border(std::list<std::shared_ptr<QixGround>> tiles, std::pair<float, float> pos);
        void move_direction(std::list<std::shared_ptr<QixGround>> tiles);
        std::pair<float, float> getObjectivePos() const;
        static char check_type_on_pos(std::pair<float, float> poscheck, std::list<std::shared_ptr<QixGround>> tiles);
        void burnTrail(void);
        int getAlive(void) const;
        std::list<std::shared_ptr<QixTrail>> getTrail() const;

    private:
        std::list<std::shared_ptr<QixTrail>> trail;
        std::pair<float, float> pos;
        std::pair<float, float> objective;
        char appearance;
        char type;
        int direction;
        int timer_move;
        int timer_burn;
        int alive;
};