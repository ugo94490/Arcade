/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** IGame
*/

#pragma once

#include <memory>
#include <list>
#include "IGameObject.hpp"

typedef struct Rect_s {
    int left;
    int top;
    int width;
    int height;
} Rect;

class IGame {
    public:
        virtual ~IGame() = default;
        virtual int handleEvents(const unsigned char &c) = 0;
        virtual void updateGame(void) = 0;
        virtual std::list<std::shared_ptr<IGameObject>> getObjects(void) const = 0;
        virtual Rect getAppearanceRectIdx(int idx) = 0;
        virtual char getAppearanceCharIdx(int idx) = 0;
};