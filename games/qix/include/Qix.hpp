/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Qix
*/

#pragma once

#include <iostream>
#include "IGame.hpp"
#include "QixPlayer.hpp"
#include "Exception.hpp"

class Qix : public IGame {
    public:
        Qix();
        ~Qix();
        int handleEvents(const unsigned char &c);
        void updateGame(void);
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        int getScore() const;
        void initGame(void);
        std::list<std::shared_ptr<QixGround>> initMap(void) const;
        std::shared_ptr<QixPlayer> initPlayer(void) const;
        std::shared_ptr<QixGround> createTile(float posx, float posy, char c) const;
        int checkWin(void) const;

    protected:
        std::shared_ptr<QixPlayer> player;
        std::shared_ptr<QixQix> qix;
        std::list<std::shared_ptr<QixSpark>> sparks;
        std::list<std::shared_ptr<QixGround>> tiles;
        int score;
        int timer_move;
    private:
};

extern "C" {
    IGame *makergame() {
        return new Qix();
    }
}