#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <SDL_ttf.h>
#include "SDL_utils.h"

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal){
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &surface, SDL_Texture* &texture,
             const string WINDOW_TITLE, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, TTF_Font* &font,
             Mix_Music* &bgm, Mix_Chunk* &beep, Mix_Chunk* &eat, Mix_Chunk* &dead)
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

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        cout << "Error 1" << endl;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        cout << "Error 2" << endl;

    bgm = Mix_LoadMUS("bgm.mp3");
    beep = Mix_LoadWAV("beep.wav");
    eat = Mix_LoadWAV("eatFood.wav");
    dead = Mix_LoadWAV("endGame.wav");
    if(bgm==NULL || beep==NULL || eat==NULL || dead==NULL)
        cout << "Error 3" << endl;

    if(TTF_Init() < 0) cout << "Error 4" << endl;

    font = TTF_OpenFont("Roboto-Black.ttf",30);
    if(!font) cout << "Error 5" << endl;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, TTF_Font *font,
             SDL_Surface* &surface, SDL_Texture* &texture,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead)
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_FreeSurface(surface);
	surface = NULL;
	Mix_FreeChunk(beep);
	Mix_FreeChunk(eat);
	Mix_FreeChunk(dead);
	Mix_FreeMusic(bgm);
	TTF_CloseFont(font);
	font = NULL;
	bgm = NULL;
	beep = NULL;
	dead = NULL;
	eat = NULL;
	TTF_Quit();
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
