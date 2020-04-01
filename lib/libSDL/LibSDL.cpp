/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSDL
*/

#include <iostream>
#include "LibSDL.hpp"

LibSDL::LibSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        throw (std::string("SDL_initialisation failed"));
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Arcade SDL", NULL);
    SDL_EnableKeyRepeat(10, 100);
}

LibSDL::~LibSDL()
{
    SDL_FreeSurface(spritesheet);
    SDL_FreeSurface(window);
    SDL_Quit();
}

void LibSDL::loadGame(const std::string &gamename)
{
    std::string spritesheetname = "games/" + gamename + "/spritesheet.png";

    SDL_WM_SetCaption((gamename + " SDL").c_str(), NULL);
    spritesheet = IMG_Load(spritesheetname.c_str());
}

char LibSDL::getEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return (-2);
        if (event.type == SDL_KEYDOWN)
            switch(event.key.keysym.sym) {
                case SDLK_n:
                    return (-3);
                    break;
                case SDLK_ESCAPE:
                    return (-2);
                    break;
                case SDLK_RETURN:
                    return (-1);
                    break;
                case SDLK_LEFT: // Flèche gauche
                    return (1);
                    break;
                case SDLK_RIGHT: // Flèche droite
                    return (2);
                    break;
                case SDLK_UP: // Flèche haut
                    return (3);
                    break;
                case SDLK_DOWN: // Flèche bas
                    return (4);
                    break;
                case SDLK_SPACE:
                    return (5);
                    break;
            }
            break;
    }
    return (0);
}

void LibSDL::draw(std::shared_ptr<IGame> game)
{
    std::list<std::shared_ptr<IGameObject>> objects = game->getObjects();
    Rect rect;
    SDL_Rect sdlrect;
    SDL_Rect sdlpos;

    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        rect = game->getAppearanceRectIdx(it->get()->getAppearance());
        sdlrect = {(short int)rect.left, (short int)rect.top,
        (Uint16)rect.width, (Uint16)rect.height};
        sdlpos.x = it->get()->getPos().first;
        sdlpos.y = it->get()->getPos().second;
        SDL_BlitSurface(spritesheet, &sdlrect, window, &sdlpos);
    }
    SDL_Flip(window);
}

void LibSDL::draw_score(int score, std::pair<float, float> pos)
{
    TTF_Init();
    std::string str = "Score " + std::to_string(score);
    TTF_Font *font = TTF_OpenFont("lib/libSFML/SNES.ttf", 55);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Rect rect = {(short)pos.first, (short)pos.second, 0, 0};
    SDL_BlitSurface(surface, NULL, window, &rect);
    SDL_Flip(window);
    SDL_FreeSurface(surface);
    TTF_Quit();
}