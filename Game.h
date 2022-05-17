#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include "CommonFunc.h"
#include "BaseObject.h"
#include "TextObject.h"



bool Check_Va_Cham( SDL_Rect& rect_column ,  SDL_Rect* rect_bird);
int Check_Score(SDL_Rect& rect_column,  SDL_Rect *rect_bird, int score, Mix_Chunk* chunk);
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);




#endif // GAME_H_INCLUDED
