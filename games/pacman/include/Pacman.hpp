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
        std::pair<float, float> checkDoor(std::pair<float, float> pos);

        std::pair<float, float> findDirection(std::shared_ptr<PacObject> obj, int dir, int index);
        std::list<std::shared_ptr<PacObject>> filleObj();
        void ctr_ghost(std::list<std::shared_ptr<PacObject>> obj);
        std::pair<float, float> move_gRed(std::shared_ptr<PacObject> obj);
        std::pair<float, float> move_gBlue(std::shared_ptr<PacObject> obj);
        std::pair<float, float> move_gOrange(std::shared_ptr<PacObject> obj);
        std::pair<float, float> move_gYellow(std::shared_ptr<PacObject> obj);
        bool checkColisionGhost(std::pair<float, float> pos);
        bool gameOver();
        bool isPriority(std::shared_ptr<PacObject> tmpObj);

        void animPacman();
    protected:
        std::list<std::shared_ptr<PacObject>> objects;
    private:
        bool _lost = false;
        size_t _dir = 1;
        size_t idxAnimPac = 0;
};

extern "C" {
    IGame *maker() {
        return new Pacman();
    }
}