#include "Game.h"
#include <iostream>

bool Check_Va_Cham( SDL_Rect& rect_column,  SDL_Rect *rect_bird)
{
     bool Va_Cham = false;
    if(  rect_column.y == 0
     && (( rect_column.y + rect_column.h) > rect_bird->y   )
     && (  rect_column.x < ( rect_bird->x + rect_bird->w ) )
     && (( rect_column.x + rect_column.w ) > rect_bird->x  ))
    {
        Va_Cham = true;
    }

    else if( rect_column.y != 0
     && (rect_column.y  < (rect_bird->y + rect_bird->h))
     && ( rect_column.x < (rect_bird->x + rect_bird->w) )
     && ( rect_column.x + rect_column.w ) > rect_bird->x )
    {
        Va_Cham = true;
    }

    else if( (rect_bird->y + BIRD_HIGHT )  >= SCREEN_HEIGHT )
    {
        Va_Cham = true;
    }

    return Va_Cham;
}



int  Check_Score(SDL_Rect& rect_column,  SDL_Rect *rect_bird, int score, Mix_Chunk * chunk)
{

    if( rect_column.y == 0 && (rect_column.x + rect_column.w) == rect_bird->x && rect_column.h !=0)
    {
        cout <<  score ++ << " ";
        Mix_PlayChannel(-1,chunk, 0);
    }
    return score;

    //if()
}

bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if(x >= rect.x && x <= rect.x + rect.w &&
       y >= rect.y && y<= rect.y + rect.h)
    {
        return true;
    }
    return false;
}


