/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSDL
*/

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "IGraphicLib.hpp"

class LibSDL : public IGraphicLib {
    public:
        LibSDL();
        ~LibSDL();
        char getEvent();
        void draw(std::shared_ptr<IGame> game);
        void loadGame(const std::string &path);
        void draw_score(int score, std::pair<float, float> pos);

    protected:
        SDL_Surface *window;
        SDL_Surface *spritesheet;
    private:
};

extern "C" {
    IGraphicLib *maker() {
        return new LibSDL();
    }
}
