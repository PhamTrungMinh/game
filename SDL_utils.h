#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string WINDOW_TITLE,
             const int SCREEN_HEIGHT, const int SCREEN_WIDTH,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead);
void logSDLError(ostream& os, const string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer,
             Mix_Music *bgm, Mix_Chunk *beep, Mix_Chunk *eat, Mix_Chunk *dead);
void waitUntilKeyPressed();
