#ifndef _MENU_H
#define _MENU_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"

using namespace std;

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

void renderText(const char* ch, int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* textRenderer);


#endif // _MENU_H
