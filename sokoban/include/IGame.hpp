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

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void handleEvents(const unsigned char &c) = 0;
        virtual void updateGame(void) = 0;
        virtual std::list<std::shared_ptr<IGameObject>> getObjects(void) const = 0;
        // classe templatée pour get un rect ou un char selon la lib
};
