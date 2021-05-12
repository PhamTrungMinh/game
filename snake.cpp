#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "SDL_utils.h"
#include "menu.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int game_h = 300, game_w = 400, game_x = 95, game_y = 245;
const string WINDOW_TITLE = "Snake";

struct Point{
    int x,y;
    int x0,y0;
};

int score, level, mode, snakeLength, big_food, highscore[5];
bool endGame;
Point direction, food, snake[200];
const int DIRECTION = 10;
SDL_Rect snake_head;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
TTF_Font *font = NULL;
Mix_Music *bgm = NULL;
Mix_Chunk *beep = NULL;
Mix_Chunk *eat = NULL;
Mix_Chunk *dead = NULL;
SDL_Rect game;

void classic();
void modern();
void mainLoop(void (*gloop)());
void play(bool& co1, bool& co2);
void changeDirecton (int x);
void showHighScore();
void getHighScore();
void checkHighScore();
void initScore();
bool isEmpty();
void run();

int main(int argc, char *argv[])
{
    initSDL(window, renderer, surface, texture, WINDOW_TITLE, SCREEN_HEIGHT, SCREEN_WIDTH,
            font, bgm, beep, eat, dead);

    run();

    quitSDL(window, renderer, font, surface, texture, bgm, beep, eat, dead);
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
    game.h = game_h; game.w = game_w;
    game.x = game_x; game.y = game_y;
    big_food = 0;
    score = 0;
    snake[0].x = 320; snake[0].y = 400;
    snake[1].x = 310; snake[1].y = 400;
    snake[2].x = 300; snake[2].y = 400;
    endGame = false;
    snakeLength = 3;
    direction.x = 10; direction.y = 0;
    srand(time(NULL));
    do{
        food.x = (rand() %40 +10)*10;
        food.y = (rand() %30 +25)*10;
    }
    while(!checkPoint());

    SDL_SetRenderDrawColor(renderer,0,150,0,255);
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Roboto-Black.ttf",50);
    renderText("SNAKE",330,50,font, blue, renderer,surface,texture);

    string s = "SCORE: ";
    stringstream ss;
    ss << score;
    s += ss.str();
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText(s,350,180,font,white,renderer,surface,texture);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    font = TTF_OpenFont("Roboto-Black.ttf",30);
    renderText("HIGHSCORE:",550,180,font,white,renderer,surface,texture);
    renderText("NO 1.",550,250,font,white,renderer,surface,texture);
    renderText("NO 2.",550,300,font,white,renderer,surface,texture);
    renderText("NO 3.",550,350,font,white,renderer,surface,texture);
    renderText("NO 4.",550,400,font,white,renderer,surface,texture);
    renderText("NO 5.",550,450,font,white,renderer,surface,texture);

    string sub;
    int i=0, n = 250;
    ifstream f("high_score.txt");
    while(!f.eof() && i<5){
        getline(f,sub);
        renderText(sub,650,n,font,white,renderer,surface,texture);
        n+=50; i++;
    }

    show_info(font,renderer,surface,texture,level,mode);
}

void drawGame(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderFillRect(renderer,&game);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&game);
    SDL_SetRenderDrawColor(renderer,0,255,0,255);

    snake_head.h=9; snake_head.w=9;
    snake_head.x=snake[0].x-4; snake_head.y=snake[0].y-4;
    SDL_RenderFillRect(renderer,&snake_head);
    for(int i=1; i<snakeLength; i++){
        SDL_RenderFillCircle(renderer,snake[i].x,snake[i].y,5);
    }
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    if(big_food==5) SDL_RenderFillCircle(renderer,food.x,food.y,7);
    else SDL_RenderFillCircle(renderer,food.x,food.y,5);
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

        if (i!=0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y)){
            endGame = true;
            Mix_PlayChannel(-1,dead,0);
        }
    }
    if (snake[0].x == food.x && snake[0].y == food.y){
        Mix_PlayChannel(-1, eat, 0);

		snake[snakeLength].x = snake[snakeLength-1].x0; snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		if(big_food==5){
            score = score +(5+level)*2;
            big_food = 0;
		}
		else{
            score = score +5 +level;
            big_food++;
		}

        string s="SCORE: ";
        stringstream ss;
        ss << score;
        s += ss.str();
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        renderText(s,350,180,font,white,renderer,surface,texture);

		srand ( time(NULL));
        do{
        	food.x = (rand() % (40) + 10)*10;
    		food.y = (rand() % (30) + 25)*10;
		}while (checkPoint() == false);
	}
	SDL_Delay(140 - 18*level);
	if(!endGame) drawGame(renderer);
}

void modern()
{
    for (int i=0; i<snakeLength; i++){
        if(i==0){
            snake[0].x0 = snake[0].x; snake[0].y0 = snake[0].y;
            snake[0].x += direction.x;
            snake[0].y += direction.y;
        }else{
            snake[i].x0 = snake[i].x; snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0; snake[i].y = snake[i-1].y0;
        }
        if (snake[i].x >= game_x+game_w) endGame = true;
        if (snake[i].x <= game_x) endGame = true;
        if (snake[i].y >= game_y+game_h) endGame = true;
        if (snake[i].y <= game_y) endGame = true;

        if (i!=0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y)){
            endGame = true;
            Mix_PlayChannel(-1,dead,0);
        }
    }
    if (snake[0].x == food.x && snake[0].y == food.y){
        Mix_PlayChannel(-1, eat, 0);

		snake[snakeLength].x = snake[snakeLength-1].x0;snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		if(big_food==5){
            score = score +(5+level)*2;
            big_food = 0;
		}
		else{
            score = score +5 +level;
            big_food++;
		}

        string s="SCORE: ";
        stringstream ss;
        ss << score;
        s += ss.str();
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        renderText(s,350,180,font,white,renderer,surface,texture);

		srand ( time(NULL));
        do{
        	food.x = (rand() % (40) + 10)*10;
    		food.y = (rand() % (30) + 25)*10;
		}while (checkPoint() == false);
	}
	SDL_Delay(140-18*level);
	if(!endGame) drawGame(renderer);
}

void changeDirecton(SDL_Event e){
    bool isRunning=true;
    while(isRunning){
        if(e.type == SDL_QUIT) isRunning = false;
        else if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_UP: case SDLK_w:
                    if (direction.y != DIRECTION) {
                        Mix_PlayChannel(-1,beep,0);
                        direction.y = -DIRECTION; direction.x = 0;
                    }
                    break;
                case SDLK_DOWN: case SDLK_s:
                    if (direction.y != -DIRECTION) {
                        Mix_PlayChannel(-1,beep,0);
                        direction.y = DIRECTION; direction.x = 0;
                    }
                    break;
                case SDLK_RIGHT: case SDLK_d:
                    if (direction.x != -DIRECTION) {
                        Mix_PlayChannel(-1,beep,0);
                        direction.x = DIRECTION; direction.y = 0;
                    }
                    break;
                case SDLK_LEFT: case SDLK_a:
                    if (direction.x != DIRECTION) {
                        Mix_PlayChannel(-1,beep,0);
                        direction.x = -DIRECTION; direction.y = 0;
                    }
                    break;
                case SDLK_ESCAPE:
                    endGame = true;
                    break;
            }
            isRunning=false;
        }
    }
}

void mainLoop(void (*xxx)())
{
    bool isRunning = true;
    SDL_Event e;
    while(!endGame && isRunning){
        xxx();
        if(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) isRunning = false;
            else if(e.type == SDL_KEYDOWN) changeDirecton(e);
        }
    }
}

void initScore()
{
    ifstream f("high_score.txt");
    int i=0;
    while(!f.eof() && i<5){
        f >> highscore[i];
        i++;
    }
    f.close();
}

void getHighScore()
{
    ofstream f("high_score.txt");
    for(int i=0; i<5; i++){
        f << highscore[i] << endl;
    }
    f.close();
}

void checkHighScore()
{
    for(int i=0; i<5; i++){
        if(highscore[i] < score){
            highscore[4] = score;
            break;
        }
    }
    sort(highscore,highscore+5,greater<int>());
}

void play(bool& co1, bool& co2)
{
    bool play = true;
    while(play){
        initGame();
        initScore();
        drawGame(renderer);
        if(mode==1)
            while(!endGame) mainLoop(classic);
        else
            while(!endGame) mainLoop(modern);

        checkHighScore();
        getHighScore();

        font = TTF_OpenFont("Roboto-Black.ttf",50);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        renderText("Ga` Ga` Ga`",200,250,font,white,renderer,surface,texture);
        renderText("Again?",200,300,font,white,renderer,surface,texture);
        renderText("1.YES",200,350,font,white,renderer,surface,texture);
        renderText("2.NO",200,400,font,white,renderer,surface,texture);

        SDL_Event e;
        bool co = true;
        while(co){
            if(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_1:
                            co = false;
                            break;
                        case SDLK_2:
                            co = false;
                            play = false;
                            co2 = false;
                            co1 = false;
                            break;
                    }
                }
            }
        }
    }
}

void run()
{
    bool run = true;
    while(run){
        if(!Mix_PlayingMusic()) Mix_PlayMusic(bgm,-1);

        menu(font, renderer, surface, texture);
        SDL_Event e;
        bool co = true;
        while(co){
            if(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_1:
                        {
                            bool co1 = true;
                            choose_mode(font,renderer,surface,texture,mode,co1);
                            while(co1){
                                bool co2 = true;
                                choose_level(font,renderer,surface,texture,level,mode,co1,co2);
                                while(co2){
                                    Mix_HaltMusic();
                                    play(co1,co2);
                                }
                            }
                            co = false;
                            break;
                        }
                        case SDLK_2:
                            how_to_play(font,renderer,surface,texture);
                            break;
                        case SDLK_3:
                            show_highscore(font,renderer,surface,texture);
                            break;
                        case SDLK_4:
                            co = false;
                            run = false;
                            break;
                        case SDLK_ESCAPE:
                            co = false;
                            break;
                    }
                }
            }
        }
    }
}
