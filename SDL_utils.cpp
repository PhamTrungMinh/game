#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"

const int game_h = 450, game_w = 600, game_x = 5, game_y = 145;

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string WINDOW_TITLE,
             const int#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_utils.h"

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string WINDOW_TITLE,
             const int SCREEN_HEIGHT, const int SCREEN_WIDTH,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        cout << "Error" << endl;

    bgm = Mix_LoadMUS("bgm.mp3");
    beep = Mix_LoadWAV("beep.wav");
    eat = Mix_LoadWAV("eatFood.wav");
    dead = Mix_LoadWAV("endGame.wav");
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead)
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	Mix_FreeChunk(beep);
	Mix_FreeChunk(eat);
	Mix_FreeChunk(dead);
	Mix_FreeMusic(bgm);
	bgm = NULL;
	beep = NULL;
	dead = NULL;
	eat = NULL;
	Mix_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_QUIT) )
            return;
        SDL_Delay(50);
    }
}
 SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect game;
    game.h = game_h; game.w = game_w;
    game.x = game_x; game.y = game_y;
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&game);

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}
