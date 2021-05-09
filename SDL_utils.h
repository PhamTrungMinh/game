#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &surface,
             SDL_Texture* &texture, const string WINDOW_TITLE,
             const int SCREEN_HEIGHT, const int SCREEN_WIDTH, TTF_Font* &font,
             Mix_Music* &bgm, Mix_Chunk* &beep, Mix_Chunk* &eat, Mix_Chunk* &dead);
void logSDLError(ostream& os, const string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer, TTF_Font *font,
             SDL_Surface* &surface, SDL_Texture* &texture,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead);
void waitUntilKeyPressed();

