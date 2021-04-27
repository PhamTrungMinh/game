#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class LButton
{
    public:
        LButton();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event* e);
        void render();

    private:
        SDL_Point mPos;
        LButtonSprite mCurrentSprite;
};

