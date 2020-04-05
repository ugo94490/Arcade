/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixPlayer
*/

#pragma once

#include "QixGround.hpp"
#include "QixTrail.hpp"
#include "QixQix.hpp"
#include "QixSpark.hpp"

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
        void check_can_move(std::list<std::shared_ptr<QixGround>> const &tiles);
        void check_can_move_border(std::list<std::shared_ptr<QixGround>> const &tiles, std::pair<float, float> const &pos);
        void move_direction(std::list<std::shared_ptr<QixGround>> const &tiles);
        std::pair<float, float> getObjectivePos() const;
        static char check_type_on_pos(std::pair<float, float> const &poscheck, std::list<std::shared_ptr<QixGround>> const &tiles);
        void burnTrail(void);
        int getAlive(void) const;
        std::list<std::shared_ptr<QixTrail>> getTrail() const;
        void check_collision_qix(std::shared_ptr<QixQix> const &qix);
        void check_collision_sparks(std::list<std::shared_ptr<QixSpark>> const &sparks);
        int try_close_trail(std::list<std::shared_ptr<QixGround>> &tiles, std::shared_ptr<QixQix> const &qix);
        int close_trail(std::list<std::shared_ptr<QixGround>> &tiles, std::shared_ptr<QixQix> const &qix);
        int isBlockTransformed(std::list<std::shared_ptr<QixGround>> tiles, std::shared_ptr<QixQix> const &qix, std::pair<float, float> blockpos);

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