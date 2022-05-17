#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include "CommonFunc.h"

using namespace std;

class BirdObject : public BaseObject
{
public:
    BirdObject();
    ~BirdObject();

    enum WalkType
    {
        WALK_UP = 0,
        WALK_DOWN = 1,
    };

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
    //float y_pos_;

    //float speed_ ;  // toc do roi tu do
    int width_frame_;
    int height_frame_;  // thong tin tung buc anh nhan vat

    SDL_Rect frame_clip_[3];    // luu 3 buc anh lam animation
    //Input input_type_;
    int frame_;  // luu chi so cua buc anh nhan vat
    int status_;  // luu trang thai nhan vat de quyet dinh dung anh nao cua nhan vat

    //= &frame_clip_[frame_]; // 1 ty thay bang frame_


    //= {rect_.x, rect_.y, width_frame_, height_frame_}; // thong tin anh xuat ra man hinh
} ;


#endif // BIRD_H_INCLUDED
