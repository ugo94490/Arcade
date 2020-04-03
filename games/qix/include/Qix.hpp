/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Qix
*/

#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "QixPlayer.hpp"
#include "QixGround.hpp"
#include "IGame.hpp"

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
        int getBlockSize() const;

        std::list<std::shared_ptr<QixGround>> initMap(void) const;
        std::shared_ptr<QixPlayer> initPlayer(void) const;
        std::shared_ptr<QixGround> createTile(float posx, float posy, char c) const;

    protected:
        std::shared_ptr<QixPlayer> player;
        std::list<std::shared_ptr<QixGround>> tiles;
        int score;
        int timer_move;
    private:
};

extern "C" {
    IGame *maker() {
        return new Qix();
    }
}