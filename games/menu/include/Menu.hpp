/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** CorePacman
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <list>
#include <memory>
#include <vector>
#include "MenuObject.hpp"
#include "IGame.hpp"


class Menu : public IGame {
    public:
        Menu();
        ~Menu();
        std::list<std::shared_ptr<MenuObject>> initGame(void);
        int handleEvents(const unsigned char &c);
        void updateGame(void) {}
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        std::shared_ptr<MenuObject> createObject(float posx, float posy, char c) const;
        int getScore() const;
        int getBlockSize() const;
        //FIN GHOST

    protected:
        std::list<std::shared_ptr<MenuObject>> objects;
    private:
        int _score;
};

extern "C" {
    IGame *maker() {
        return new Menu();
    }
}