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

void renderText(const string s, int x, int y, TTF_Font* &font, SDL_Color color,
        SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture)
{
    surface = TTF_RenderText_Solid(font, s.c_str(), color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect Message_rect, srcRest;
    TTF_SizeText(font,s.c_str(),&srcRest.w,&srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = srcRest.w;
    Message_rect.h = srcRest.h;

    SDL_RenderFillRect(renderer,&Message_rect);
    SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
    SDL_RenderPresent(renderer);
}

void menu(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture)
{
    SDL_SetRenderDrawColor(renderer,0,200,0,255);
    SDL_RenderClear(renderer);
    renderText("SNAKE",350,0,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    renderText("START",350,200,font, white, renderer,surface,texture);
    renderText("HIGHSCORE",320,300,font, white, renderer,surface,texture);
    renderText("QUIT",365,400,font, white, renderer,surface,texture);
}
