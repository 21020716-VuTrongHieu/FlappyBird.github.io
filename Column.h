#ifndef COLUMN_H_INCLUDED
#define COLUMN_H_INCLUDED


#include "CommonFunc.h"

class ColumnObject : public BaseObject
{
public:
    ColumnObject();
    ~ColumnObject();

    bool LoadImg(string path, SDL_Renderer* render);
    void Show(SDL_Renderer* des, SDL_Rect& rect);
    void Column_Run();

    void Set_Column_Clip(int x, int y, int w, int h);

    SDL_Rect column_clip_;
    SDL_Rect renderQuad_1 ;
    SDL_Rect renderQuad_cot_tren ;
    SDL_Rect renderQuad_cot_duoi ;


//private:
    float x_val_;
    float y_val_;   // thay doi cua nhan vat tren man hinh

    float x_pos_; // thong tin vi tri xuat nhan vat ra man hinh
    float y_pos_;







};



#endif // COLUMN_H_INCLUDED
