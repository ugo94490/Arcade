/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sokoban
*/

#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "SokoObject.hpp"
#include "IGame.hpp"

class Sokoban : public IGame {
    public:
        Sokoban();
        ~Sokoban();
        std::list<std::shared_ptr<SokoObject>> initGame(void) const;
        int handleEvents(const unsigned char &c);
        void updateGame(void) {}
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        std::shared_ptr<SokoObject> createObject(float posx, float posy, char c) const;
        std::shared_ptr<SokoObject> check_free(std::pair<float, float> pos) const;
        int move_object(std::shared_ptr<SokoObject> obj, int direction);
        int getScore() const;

    protected:
        std::list<std::shared_ptr<SokoObject>> objects;
    private:
        int score;
};

extern "C" {
    IGame *makergame() {
        return new Sokoban();
    }
}