/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibSDL
*/

#include <iostream>
#include "LibSDL.hpp"

static const double factor_x = 0.5;
static const double factor_y = 0.5;

LibSDL::LibSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        throw (std::string("SDL_initialisation failed"));
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Arcade SDL", NULL);
    SDL_EnableKeyRepeat(10, 100);
    TTF_Init();
}

LibSDL::~LibSDL()
{
    TTF_Quit();
    SDL_FreeSurface(surface);
    SDL_FreeSurface(spritesheet);
    SDL_FreeSurface(window);
    SDL_Quit();
}

Uint32 LibSDL::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;
    case 2:
        return *(Uint16 *)p;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        return *(Uint32 *)p;
        break;
    default:
        return 0;
    }
}

void LibSDL::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

SDL_Surface *LibSDL::ScaleSurface(SDL_Surface *Surface, double _stretch_factor_x, double _stretch_factor_y)
{
    if(!Surface)
        return 0;
    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Surface->w * _stretch_factor_x, Surface->h * _stretch_factor_y, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
    for(Sint32 y = 0; y < Surface->h; y++)
        for(Sint32 x = 0; x < Surface->w; x++)
            for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    putpixel(_ret, static_cast<Sint32>(_stretch_factor_x * x) + o_x, 
                        static_cast<Sint32>(_stretch_factor_y * y) + o_y, getpixel(Surface, x, y));
    return _ret;
}

void LibSDL::loadGame(const std::string &gamename)
{
    std::string spritesheetname = "games/" + gamename + "/spritesheet.png";

    SDL_WM_SetCaption((gamename + " SDL").c_str(), NULL);
    spritesheet = IMG_Load(spritesheetname.c_str());
    spritesheet = ScaleSurface(spritesheet, factor_x, factor_y);
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
        sdlrect = {(short int)rect.left * factor_x, (short int)rect.top * factor_y,
        (Uint16)rect.width * factor_x, (Uint16)rect.height * factor_y};
        sdlpos.x = it->get()->getPos().first;
        sdlpos.y = it->get()->getPos().second;
        SDL_BlitSurface(spritesheet, &sdlrect, window, &sdlpos);
    }
    SDL_Flip(window);
}

void LibSDL::draw_score(int score, std::pair<float, float> pos)
{
    std::string str = "Score " + std::to_string(score);
    SDL_Color color = {255, 255, 255};
    surface = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Rect rect = {(short)pos.first, (short)pos.second, 0, 0};
    SDL_BlitSurface(surface, NULL, window, &rect);
    SDL_Flip(window);
}

void LibSDL::gameOver(int score)
{
    
}

void LibSDL::init_score(int score, std::pair<float, float> pos)
{
    font = TTF_OpenFont("lib/libSFML/SNES.ttf", 55);
}