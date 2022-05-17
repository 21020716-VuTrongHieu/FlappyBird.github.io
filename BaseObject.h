#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFunc.h"
using namespace std;

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void SetRect (const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect()
    {
        return rect_;
    }

    virtual bool LoadImg(string path, SDL_Renderer* render);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();



protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
    SDL_Rect renderquad;

    SDL_Texture* new_texture ;//= NULL;

    SDL_Surface* load_surface ;// = IMG_Load(path.c_str());

};


#endif // BASEOBJECT_H_INCLUDED
