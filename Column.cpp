#include "Column.h"
#include <iostream>

using namespace std;

ColumnObject::ColumnObject()
{
    x_pos_ = -100;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
}


ColumnObject::~ColumnObject()
{

}

bool ColumnObject::LoadImg(string path,SDL_Renderer* render)
{
    BaseObject::LoadImg(path,render);
}

void ColumnObject::Show(SDL_Renderer* des, SDL_Rect& rect )
{
    y_pos_ = rect.y;
    if( x_pos_ == -100 )
    {
        x_pos_ = rect.x;
        x_val_ = rect.x;
    }
    else
    {
        x_pos_ = x_val_;
    }

     renderQuad_1 = {x_pos_, y_pos_,rect.w,rect.h};
     renderQuad_cot_tren = {0, COLUMN_HIGHT - rect.h, 60, rect.h};
     renderQuad_cot_duoi = {0, 0, 60, SCREEN_HEIGHT - y_pos_  };


    if(y_pos_ == 0)
    {
        SDL_RenderCopy(des,p_object_,&renderQuad_cot_tren,&renderQuad_1);
    }
    else
    {
        SDL_RenderCopy(des,p_object_,&renderQuad_cot_duoi,&renderQuad_1);
    }
    
}


void ColumnObject::Column_Run()
{
      x_val_ = x_val_ - COLUMN_SPEED;
}

void ColumnObject::Set_Column_Clip(int x, int y, int w, int h)
{
      column_clip_.x = x;
      column_clip_.y = y;
      column_clip_.w = w;
      column_clip_.h = h;
}



