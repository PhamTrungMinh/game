#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
#include <sstream>
#include "menu.h"
#include "SDL_utils.h"

using namespace std;

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
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("1.START",350,250,font, white, renderer,surface,texture);
    renderText("2.HOW TO PLAY",300,300,font,white,renderer,surface,texture);
    renderText("3.HIGHSCORE",320,350,font, white, renderer,surface,texture);
    renderText("4.QUIT",365,400,font, white, renderer,surface,texture);
}

void choose_mode(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture,
                 int& mode, bool& co1)
{
    SDL_SetRenderDrawColor(renderer,0,200,0,255);
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("CHOOSE MODE:",200,250,font,white,renderer,surface,texture);
    renderText("1.CLASSIC",450,250,font,white,renderer,surface,texture);
    renderText("2.MODERN",450,300,font,white,renderer,surface,texture);

    SDL_Event e;
    bool co = true;
    while(co){
        if(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_1:
                        mode = 1;
                        break;
                    case SDLK_2:
                        mode = 2;
                        break;
                    case SDLK_ESCAPE:
                        co1 = false;
                        break;
                }
                co = false;
            }
        }
    }
}

void choose_level(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture,
                  int &level, int& mode, bool& co1, bool& co2)
{
    SDL_SetRenderDrawColor(renderer,0,200,0,255);
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("CHOOSE LEVEL:",200,250,font,white,renderer,surface,texture);
    renderText("1",440,250,font,white,renderer,surface,texture);
    renderText("2",480,250,font,white,renderer,surface,texture);
    renderText("3",520,250,font,white,renderer,surface,texture);
    renderText("4",560,250,font,white,renderer,surface,texture);
    renderText("5",600,250,font,white,renderer,surface,texture);

    SDL_Event e;
    bool co = true;
    while(co){
        if(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_1:
                        level = 1;
                        break;
                    case SDLK_2:
                        level = 2;
                        break;
                    case SDLK_3:
                        level = 3;
                        break;
                    case SDLK_4:
                        level = 4;
                        break;
                    case SDLK_5:
                        level = 5;
                        break;
                    case SDLK_ESCAPE:
                        co2 = false;
                        choose_mode(font,renderer,surface,texture,mode,co1);
                        break;
                }
                co = false;
            }
        }
    }
}

void how_to_play(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture)
{
    SDL_SetRenderDrawColor(renderer,0,200,0,255);
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("HOW TO PLAY",320,150,font,white,renderer,surface,texture);
    renderText("ARROW UP/ W: MOVE UP",200,250,font,white,renderer,surface,texture);
    renderText("ARROW RIGHT/ D: MOVE RIGHT",200,300,font,white,renderer,surface,texture);
    renderText("ARROW DOWN/ S: MOVE DOWN",200,350,font,white,renderer,surface,texture);
    renderText("ARROW LEFT/ A: MOVE LEFT",200,400,font,white,renderer,surface,texture);
}

void show_highscore(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture)
{
    SDL_SetRenderDrawColor(renderer,0,200,0,255);
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("HIGHSCORE",325,150,font,white,renderer,surface,texture);
    renderText("NO 1.",330,250,font,white,renderer,surface,texture);
    renderText("NO 2.",330,300,font,white,renderer,surface,texture);
    renderText("NO 3.",330,350,font,white,renderer,surface,texture);
    renderText("NO 4.",330,400,font,white,renderer,surface,texture);
    renderText("NO 5.",330,450,font,white,renderer,surface,texture);

    string s;
    int i=0, n = 250;
    ifstream f("high_score.txt");
    while(!f.eof() && i<5){
        getline(f,s);
        renderText(s,430,n,font,white,renderer,surface,texture);
        n+=50; i++;
    }
}

void show_info(TTF_Font* &font, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture, int& level, int& mode)
{
    string s="LEVEL: ";
    stringstream ss;
    ss << level;
    s += ss.str();
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText(s,100,120,font,white,renderer,surface,texture);
    if(mode==1)
        renderText("MODE: CLASSIC",100,180,font,white,renderer,surface,texture);
    else renderText("MODE: MODERN",100,180,font,white,renderer,surface,texture);
}
