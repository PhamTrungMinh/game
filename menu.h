#ifndef _MENU_H
#define _MENU_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"

using namespace std;

static SDL_Color white = {255, 255, 255, 255};
static SDL_Color blue = {0, 0, 200, 255};

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class LButton
{
    public:
        LButton();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event* e);
        void render();

    private:
        SDL_Point mPos;
        LButtonSprite mCurrentSprite;
};

void renderText(const string s, int x, int y, TTF_Font* &font, SDL_Color color,
        SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture);

void menu(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture);

#endif // _MENU_H

