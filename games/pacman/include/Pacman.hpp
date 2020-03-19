/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "PacObject.hpp"
#include "IGame.hpp"

class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();
        std::list<std::shared_ptr<PacObject>> initGame(void) const;
        void handleEvents(const unsigned char &c);
        void updateGame(void) {}
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        std::shared_ptr<PacObject> createObject(float posx, float posy, char c) const;
        int move_object(std::shared_ptr<PacObject> obj, int direction);
        bool checkColision(std::pair<float, float> pos);
        void checkStar(std::pair<float, float> pos);

    protected:
        std::list<std::shared_ptr<PacObject>> objects;
    private:
};

extern "C" {
    IGame *maker() {
        return new Pacman();
    }
}