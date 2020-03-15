/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameObject
*/

#pragma once

#include <utility>

class IGameObject {
    public:
        virtual ~IGameObject() = default;
        virtual std::pair<float, float> getPos() const = 0;
        virtual char getAppearance() const = 0;
};
