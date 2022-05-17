#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "CommonFunc.h"

using namespace std;

class BirdObject : public BaseObject
{
public:
    BirdObject();
    ~BirdObject();

    bool LoadImg(string path, SDL_Renderer* render);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* render);
    void set_clips();
    void DoPlayer();

    SDL_Rect* current_clip;
    SDL_Rect renderQuad;

    float y_pos_;
    float speed_;
    Input input_type_;


private:
    float x_val_;
    float y_val_;   // thay doi cua nhan vat tren man hinh
    float x_pos_; // thong tin vi tri xuat nhan vat ra man hinh
    int width_frame_;
    int height_frame_;  // thong tin tung buc anh nhan vat
    SDL_Rect frame_clip_[3];    // luu 3 buc anh lam animation
    int frame_;  // luu chi so cua buc anh nhan vat
} ;


#endif // BIRD_H_INCLUDED
