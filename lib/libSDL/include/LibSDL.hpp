/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSDL
*/

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "IGraphicLib.hpp"

class LibSDL : public IGraphicLib {
    public:
        LibSDL();
        ~LibSDL();
        char getEvent();
        void draw(std::shared_ptr<IGame> game);
        void loadGame(const std::string &path);
        void draw_score(int score, std::pair<float, float> pos);
        void gameOver(int score);

        Uint32 getpixel(SDL_Surface *surface, int x, int y);
        void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
        SDL_Surface *ScaleSurface(SDL_Surface *Surface, double _stretch_factor_x, double _stretch_factor_y);

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
