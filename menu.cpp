#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "menu.h"
#include "SDL_utils.h"

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
        bool inside = true;
    }
}

void renderText(const char* ch, int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* &textRenderer)
{
    SDL_Color color = {0, 0, 255, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ch, color);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(textRenderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = w;
    Message_rect.h = h;
    SDL_RenderCopy(textRenderer, Message, NULL, &Message_rect);
}
