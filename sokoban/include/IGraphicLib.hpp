/*
** EPITECH PROJECT, 2020
** sokoban
** File description:
** IGraphicLib
*/

#pragma once

#include <string>
#include <list>
#include <memory>
#include "IGameObject.hpp"

class IGraphicLib {
    public:
        virtual ~IGraphicLib() = default;
        virtual char getEvent() = 0;
        virtual void draw(std::list<std::shared_ptr<IGameObject>> objects) = 0;
};
