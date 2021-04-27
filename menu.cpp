#include <iostream>
#include <string>
#include <SDL.h>
#include "menu.h"

using namespace std;

LButton::LButton()
{
    mPos.x = 0;
    mPos.y = 0;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
    mPos.x = x;
    mPos.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
    }
}
