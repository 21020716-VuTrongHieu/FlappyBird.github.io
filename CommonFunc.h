#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include "windows.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "BaseObject.h"
#include <SDL_mixer.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_render = NULL;
static SDL_Event g_event;

//MIXER

static Mix_Chunk *Ball_tap = NULL;
static Mix_Chunk *Hit = NULL;
static Mix_Chunk *Ting = NULL;
static Mix_Music *Music = NULL;


//SCREEN
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;


//Input
typedef struct Input
{
    int up_;
    int down_;
};

//GiaToc

const int G = 3;

//Column
const int COLUMN_WIDTH = 60;
const int COLUMN_HIGHT = 500;
const int COLUMN_SPEED = 5;
const int COLUMN_BLANK = 150;  // khoang cach ong tren va duoi
const int COLUMN_DISTANCE = 300; // khoang cach 2 cot canh nhau

//Bird
const int BIRD_WIDTH = 60;
const int BIRD_HIGHT = 46;

//FPS
const int FPS = 25;


#endif // COMMONFUNC_H_INCLUDED
