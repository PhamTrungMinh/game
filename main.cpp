#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <time.h>
#include "SDL_utils.h"
//#include "moving.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake";

struct Point{
    int x,y;
    int x0,y0;
};

struct HighScore {
    int score;
    char name[30];
};

int level;
bool endGame;
int snakeLength;
Point snake[150];
Point direction;
Point food;
const int DIRECTION = 10;
HighScore  highscore[5];

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void initGame ();
bool checkPoint ();
void moveSnake ();
void drawGame (SDL_Renderer* renderer);
void classic();
void modern();
void mainLoop (void (*gloop)());
void run ();
void changeDirecton (int x);
void showHighScore();
void getHighScore();
void checkHighScore(int score);
void initScore();
bool isEmpty();
void showText(int x,int y,char *str);
void showTextBackground(int x,int y,char *str,int color);

int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, WINDOW_TITLE, SCREEN_HEIGHT, SCREEN_WIDTH);

    initGame();
    drawGame(renderer);

    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    quitSDL(window,renderer);
    return 0;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

bool checkPoint (){
	for (int i = 0;i < snakeLength;i++){
		if (food.x == snake[i].x && food.y == snake[i].y)
		return false;
	}
	return true;
}

void initGame()
{
    snake[0].x = 320; snake[0].y = 400;
    snake[1].x = 310; snake[1].y = 400;
    snake[2].x = 300; snake[2].y = 400;
    endGame = false;
    snakeLength = 3;
    direction.x = 10; direction.y = 0;
    srand(time(NULL));
    do{
        food.x = (rand() %60 +1)*10;
        food.y = (rand() %45 +15)*10;
    }
    while(!checkPoint());
}

void drawGame(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    for(int i=0; i<snakeLength; i++){
        SDL_RenderFillCircle(renderer,snake[i].x,snake[i].y,5);
    }
    int i=rand() %3 +1;
    if(i==1) SDL_SetRenderDrawColor(renderer,0,255,0,255);
    else if(i==2) SDL_SetRenderDrawColor(renderer,0,0,255,255);
    else SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillCircle(renderer,food.x,food.y,5);
    SDL_RenderPresent(renderer);
}
