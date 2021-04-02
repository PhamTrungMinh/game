#include <iostream>
#include <SDL.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string WINDOW_TITLE,
             const int SCREEN_HEIGHT, const int SCREEN_WIDTH);
void logSDLError(ostream& os, const string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

