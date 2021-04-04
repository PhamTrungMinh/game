#include <iostream>
#include <SDL.h>
#include <vector>
#include <time.h>
#include "SDL_utils.h"
//#include "moving.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int game_h = 450, game_w = 600, game_x = 5, game_y = 145;
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
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect game;

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
    initSDL(window, renderer, WINDOW_TITLE, SCREEN_HEIGHT, SCREEN_WIDTH);

    run();

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
    game.h = game_h; game.w = game_w;
    game.x = game_x; game.y = game_y;
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&game);
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

void classic(){
    for (int i=0; i<snakeLength; i++){
        if(i==0){
            snake[0].x0 = snake[0].x; snake[0].y0 = snake[0].y;
            snake[0].x += direction.x;
            snake[0].y += direction.y;
        }else{
            snake[i].x0 = snake[i].x; snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0; snake[i].y = snake[i-1].y0;
        }
        if (snake[i].x >= game_x+game_w) snake[i].x = game_x + 5;
        if (snake[i].x <= game_x) snake[i].x = game_x+game_w - 5;
        if (snake[i].y >= game_y+game_h) snake[i].y = game_y + 5;
        if (snake[i].y <= game_y) snake[i].y = game_y+game_h - 5;

        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) endGame = true;
    }
    if (snake[0].x == food.x && snake[0].y == food.y){
		snake[snakeLength].x = snake[snakeLength-1].x0;snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		srand ( time(NULL));
        do{
        	food.x = (rand() % (60) + 1)*10;
    		food.y = (rand() % (45) + 15)*10;
		}while (checkPoint() == false);
	}
}

void changeDirecton(SDL_Event e){
    bool isRunning=true;
    while(isRunning){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) isRunning = false;
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        if (direction.y != DIRECTION) {
                            //PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                            direction.y = -DIRECTION; direction.x = 0;
                        }
                        break;
                    case SDLK_DOWN:
                        if (direction.y != -DIRECTION) {
                            //PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                            direction.y = DIRECTION; direction.x = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (direction.x != -DIRECTION) {
                            //PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                            direction.x = DIRECTION; direction.y = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        if (direction.x != DIRECTION) {
                            //PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
                            direction.x = -DIRECTION; direction.y = 0;
                        }
                        break;
                    case SDLK_ESCAPE:
                        endGame = true;
                        break;
                }
            }
        }
    }
}

void mainLoop(void (*xxx)())
{
    SDL_Delay(100);
    bool isRunning=true;
    SDL_Event e;
    while(isRunning){
        if(SDL_PollEvent(&e)==0){
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            drawGame(renderer);
            classic();
        }
        else{
            if(e.type == SDL_QUIT) isRunning = false;
            else if(e.type == SDL_KEYDOWN){
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                changeDirecton(e);
                drawGame(renderer);
                mainLoop(xxx);
            }
        }
    }
}

void run()
{
    initGame();
    drawGame(renderer);
    while(endGame==false){
        SDL_RenderClear(renderer);
        mainLoop(classic);
        drawGame(renderer);
    }
}
