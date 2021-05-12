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

void renderText(const string s, int x, int y, TTF_Font* &font, SDL_Color color,
        SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture);

void menu(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface,
          SDL_Texture* &texture);

void choose_mode(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture,
                 int& mode, bool& co1);

void choose_level(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture,
                  int &level, int& mode, bool& co1, bool& co2);

void how_to_play(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture);

void show_highscore(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture);

void show_info(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture, int& level, int& mode);

#endif // _MENU_H
