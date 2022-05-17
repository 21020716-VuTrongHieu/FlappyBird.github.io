#include "Bird.h"
#include <iostream>
using namespace std;

BirdObject::BirdObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 80;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    speed_ = 0;


}

BirdObject::~BirdObject()
{

}

bool BirdObject::LoadImg(string path, SDL_Renderer* render)
{
     BaseObject::LoadImg(path,render);
     width_frame_ = BIRD_WIDTH ;  // lay thong tin anh
     height_frame_ = BIRD_HIGHT ;

}

void BirdObject::set_clips()
{

        frame_clip_[0].x = 220;    // lay kich thuoc anh
        frame_clip_[0].y = 155;
        frame_clip_[0].w = 220;
        frame_clip_[0].h = 170;  // chu y ty nua chinh lai bang tay


        frame_clip_[1].x = 480;    // lay kich thuoc anh
        frame_clip_[1].y = 155;
        frame_clip_[1].w = 220;
        frame_clip_[1].h = 170;

        frame_clip_[2].x = 730;    // lay kich thuoc anh
        frame_clip_[2].y = 155;
        frame_clip_[2].w = 220;
        frame_clip_[2].h = 170;

}

void BirdObject::Show(SDL_Renderer* des)
{

    rect_.x = x_pos_;
    rect_.y = y_pos_;
    frame_ ++;
    if(frame_ >=3)
    {
        frame_ = 0;
    }


    current_clip = &frame_clip_[frame_]; // 1 ty thay bang frame_
    renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_}; // thong tin anh xuat ra man hinh

    SDL_RenderCopy(des, p_object_, current_clip,&renderQuad);
}

void BirdObject::HandelInputAction(SDL_Event events, SDL_Renderer* render)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_SPACE:
            {
                input_type_.up_ = 1;
                input_type_.down_ = 0;
            }
            break;

        default:
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_SPACE:
            {
                input_type_.down_ = 1;
                input_type_.up_ = 0;
            }
            break;

        default:
            break;
        }
    }
}

void BirdObject::DoPlayer()
{
    x_pos_ = 80;
    y_pos_ = y_pos_ + speed_ + 0.5*G;    // vi tri moi theo gia toc roi
    speed_ += G;               // dieu chinh toc do roi cua chim tai day

    if(input_type_.up_ == 1)
    {
         speed_ = 0;
         x_pos_ = 80;
         y_pos_ = y_pos_ - 20;  // 20 la khoang bay len

    }

}
