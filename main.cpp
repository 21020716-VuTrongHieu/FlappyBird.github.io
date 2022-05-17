#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bird.h"
#include "Column.h"
#include "ImpTimer.h"
#include "Game.h"
#include <ctime>
#include "TextObject.h"

using namespace std;

BaseObject g_background;
BaseObject g_game_start;
BaseObject g_game_over;

TTF_Font* font_score = NULL;
TTF_Font* font_menu = NULL;


bool InitData()
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    if(ret<0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow("Flappy Bird",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);

    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_render == NULL)
        {
            success = false;
        }


        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_score = TTF_OpenFont("font/aachenb.ttf",35);
        font_menu = TTF_OpenFont("font/aachenb.ttf",55);
        if(font_score == NULL && font_menu == NULL)
        {
            success = false;
        }
    }

   return success;
}

bool LoadBackground()
{
    bool ret_1 = g_background.LoadImg("FlappyBird_image/AnhNen_2.bmp",g_render);
    bool ret_2 = g_game_start.LoadImg("FlappyBird_image/Menu_Start.bmp",g_render);
    bool ret_3 = g_game_over.LoadImg("FlappyBird_image/Menu_GameOver.bmp",g_render);
   if(ret_1 == false && ret_2 == false && ret_3 == false ) return false;

   if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) return false;

   Ball_tap = Mix_LoadWAV( "Sound/Ball_tap.wav" );
   Ting = Mix_LoadWAV( "Sound/Ting.wav" );
   Hit = Mix_LoadWAV( "Sound/Hit.wav" );
   Music = Mix_LoadMUS("Sound/yamate.wav");
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_render);
    g_render = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}



int ShowMenuStart(TTF_Font* font)
{
  const int MenuItemStart = 2;
  SDL_Rect pos_arr[MenuItemStart];

  int xm=0;
  int ym=0;

  pos_arr[0].x = 160;
  pos_arr[0].y = 330;
  pos_arr[0].w = 270;
  pos_arr[0].h = 45;

  pos_arr[1].x = 160;
  pos_arr[1].y = 410;
  pos_arr[1].w = 100;
  pos_arr[1].h = 45;

  TextObject text_menu_start[MenuItemStart];

  text_menu_start[0].SetText("Play Game");
  text_menu_start[0].SetColor(TextObject::WHITE_TEXT);
 
  text_menu_start[1].SetText("Exit");
  text_menu_start[1].SetColor(TextObject::WHITE_TEXT);

  bool selected[MenuItemStart] = {0, 0};

  SDL_Event m_event;

  while(true)
  {
      SDL_RenderClear(g_render);
      g_game_start.Render(g_render, NULL);

      for(int i =0; i<MenuItemStart; i++)
      {
          text_menu_start[i].LoadFromRenderText(font,g_render);
      }
      text_menu_start[0].RenderText(g_render,pos_arr[0].x , pos_arr[0].y);
      text_menu_start[1].RenderText(g_render,pos_arr[1].x , pos_arr[1].y);

      while(SDL_PollEvent(&m_event))
      {
          switch(m_event.type)
          {
            case SDL_QUIT:
               return 1;
            case SDL_MOUSEMOTION:
              {
                  xm = m_event.motion.x;
                  ym = m_event.motion.y;

                  for(int i=0; i< MenuItemStart; i++)
                  {
                      if(CheckFocusWithRect(xm,ym, pos_arr[i]))
                      {
                          if(selected[i] == false)
                          {
                              selected[i] = 1;
                              text_menu_start[i].SetColor(TextObject::RED_TEXT);
                          }
                      }
                      else
                      {
                          if(selected[i] == true)
                          {
                              selected[i] = 0;
                              text_menu_start[i].SetColor(TextObject::WHITE_TEXT);
                          }
                      }
                  }
              }
             case SDL_MOUSEBUTTONDOWN:
              {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for(int i=0; i<MenuItemStart; i++)
                {
                     if(CheckFocusWithRect(xm,ym, pos_arr[i]))
                     {
                         if (m_event.button.button == SDL_BUTTON_LEFT)
                         {
                             Mix_PlayChannel(-1,Ball_tap, 0);
                             return i;
                         }
                     }
                }
              }

             default:
                break;
          }
      }

      SDL_RenderPresent(g_render);
  }
  return 1;
}

int ShowMenuGameOver(TTF_Font* font, string score)
{
  const int MenuItemOver = 3;
  SDL_Rect pos_arr[MenuItemOver];

  int xm=0;
  int ym=0;

  pos_arr[0].x = 500;
  pos_arr[0].y = 250;
  pos_arr[0].w = 175;
  pos_arr[0].h = 30;

  pos_arr[1].x = 500;
  pos_arr[1].y = 330;
  pos_arr[1].w = 60;
  pos_arr[1].h = 30;

  pos_arr[2].x = 300;
  pos_arr[2].y = 290;
  pos_arr[2].w = 120;
  pos_arr[2].h = 30;

  TextObject text_menu_over[MenuItemOver];

  text_menu_over[0].SetText("Play Again");
  text_menu_over[0].SetColor(TextObject::WHITE_TEXT);
  //text_menu_start[0].

  text_menu_over[1].SetText("Exit");
  text_menu_over[1].SetColor(TextObject::WHITE_TEXT);

  text_menu_over[2].SetText(score);
  text_menu_over[2].SetColor(TextObject::WHITE_TEXT);

  bool selected[MenuItemOver ] = {0, 0, 0};

  SDL_Event m_event;

  while(true)
  {
      SDL_RenderClear(g_render);
      g_game_over.Render(g_render, NULL);

      //score_game.LoadFromRenderText(font_score,g_render);
      //score_game.RenderText(g_render,SCREEN_WIDTH -200 , 15);

      for(int i =0; i<MenuItemOver; i++)
      {
          text_menu_over[i].LoadFromRenderText(font,g_render);
      }
      text_menu_over[0].RenderText(g_render,pos_arr[0].x , pos_arr[0].y);
      text_menu_over[1].RenderText(g_render,pos_arr[1].x , pos_arr[1].y);
      text_menu_over[2].RenderText(g_render,pos_arr[2].x , pos_arr[2].y);

      while(SDL_PollEvent(&m_event))
      {
          switch(m_event.type)
          {
            case SDL_QUIT:
               return 1;
            case SDL_MOUSEMOTION:
              {
                  xm = m_event.motion.x;
                  ym = m_event.motion.y;

                  for(int i=0; i< MenuItemOver -1; i++)
                  {
                      if(CheckFocusWithRect(xm,ym, pos_arr[i]))
                      {
                          if(selected[i] == false)
                          {
                              selected[i] = 1;
                              text_menu_over[i].SetColor(TextObject::RED_TEXT);
                          }
                      }
                      else
                      {
                          if(selected[i] == true)
                          {
                              selected[i] = 0;
                              text_menu_over[i].SetColor(TextObject::WHITE_TEXT);
                          }
                      }
                  }
              }
             case SDL_MOUSEBUTTONDOWN:
              {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for(int i=0; i<MenuItemOver -1 ; i++)
                {
                     if(CheckFocusWithRect(xm,ym, pos_arr[i]))
                     {
                         if (m_event.button.button == SDL_BUTTON_LEFT)
                         {
                             Mix_PlayChannel(-1,Ball_tap, 0);
                             return i;
                         }
                     }
                }
              }

             default:
                break;
          }
      }

      SDL_RenderPresent(g_render);
  }
  return 1;
}

int main(int argc, char* argv[])
{
    ImpTimer FPS_Timer;

    srand(time(0));

    if(InitData() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;

        // Bird
    BirdObject p_player;
    p_player.LoadImg("FlappyBird_image/Chim.bmp",g_render);
    p_player.set_clips();


       //Column

    ColumnObject p_column[4][2];
    for(int i=0; i<4; i++)
    {
        p_column[i][0].LoadImg("FlappyBird_image/Cot.bmp",g_render);
        p_column[i][1].LoadImg("FlappyBird_image/Cot.bmp",g_render);
    }

    SDL_Rect column_rect[4][2];

    // cot 1
        p_column[0][0].Set_Column_Clip(300,
                                       0,
                                       COLUMN_WIDTH,
                                       rand() % 380 +50);
        column_rect[0][0] = p_column[0][0].column_clip_;


        p_column[0][1].Set_Column_Clip(column_rect[0][0].x,
                                       column_rect[0][0].h + COLUMN_BLANK,
                                       COLUMN_WIDTH,
                                       SCREEN_HEIGHT - column_rect[0][0].h - COLUMN_BLANK);
        column_rect[0][1] = p_column[0][1].column_clip_;


        // cot 2
        p_column[1][0].Set_Column_Clip(column_rect[0][0].x + COLUMN_DISTANCE,
                                       0,
                                       COLUMN_WIDTH,
                                       rand() % 380 + 50);
        column_rect[1][0] = p_column[1][0].column_clip_;


        p_column[1][1].Set_Column_Clip(column_rect[1][0].x,
                                       column_rect[1][0].h + COLUMN_BLANK,
                                       COLUMN_WIDTH,
                                       SCREEN_HEIGHT - column_rect[1][0].h - COLUMN_BLANK);
        column_rect[1][1] = p_column[1][1].column_clip_;

        // cot 3
        p_column[2][0].Set_Column_Clip(column_rect[1][0].x + COLUMN_DISTANCE,
                                       0,
                                       COLUMN_WIDTH,
                                       rand() % 380 + 50);
        column_rect[2][0] = p_column[2][0].column_clip_;


        p_column[2][1].Set_Column_Clip(column_rect[2][0].x,
                                       column_rect[2][0].h + COLUMN_BLANK,
                                       COLUMN_WIDTH,
                                       SCREEN_HEIGHT - column_rect[2][0].h - COLUMN_BLANK);
        column_rect[2][1] = p_column[2][1].column_clip_;

        // cot 4
        p_column[3][0].Set_Column_Clip(column_rect[2][0].x + COLUMN_DISTANCE,
                                       0,
                                       COLUMN_WIDTH,
                                       rand() % 380 + 50);
        column_rect[3][0] = p_column[3][0].column_clip_;


        p_column[3][1].Set_Column_Clip(column_rect[3][0].x,
                                       column_rect[3][0].h + COLUMN_BLANK,
                                       COLUMN_WIDTH,
                                       SCREEN_HEIGHT - column_rect[3][0].h - COLUMN_BLANK);
        column_rect[3][1] = p_column[3][1].column_clip_;


  //SCORE Text
    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);  //enum
    UINT32 score_ =0;

    bool is_quit = false;
    bool is_gameover = false;

    int ret_menu_start = ShowMenuStart(font_menu);
    if(ret_menu_start == 1)
    {
        is_quit = true;
    }


while(!is_quit)
{

   Mix_PlayMusic(Music,-1);  // chay nhac nen
   while(!is_quit)
    {
        FPS_Timer.start();

        while(SDL_PollEvent(&g_event) !=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandelInputAction(g_event,g_render);

        }

        SDL_RenderClear(g_render);


        // dua background len man hinh
        g_background.Render(g_render,NULL);
        
        // dua con chim len man hinh
        p_player.Show(g_render);
        p_player.DoPlayer();

        // dua cot ra man hinh

        //cot 1
        p_column[0][0].Show(g_render,column_rect[0][0]);
        p_column[0][1].Show(g_render,column_rect[0][1]);
        p_column[0][0].Column_Run();
        p_column[0][1].Column_Run();
        if( p_column[0][0].x_pos_ == - COLUMN_WIDTH )
        {
            p_column[0][0].Set_Column_Clip(p_column[3][0].x_pos_ + COLUMN_DISTANCE - COLUMN_WIDTH,
                                           0,
                                           COLUMN_WIDTH,
                                           rand() % 380 + 50);
            column_rect[0][0] = p_column[0][0].column_clip_;


            p_column[0][1].Set_Column_Clip(p_column[0][0].column_clip_.x,
                                           p_column[0][0].column_clip_.h + COLUMN_BLANK,
                                           COLUMN_WIDTH,
                                           SCREEN_HEIGHT - p_column[0][0].column_clip_.h - COLUMN_BLANK);
            column_rect[0][1] = p_column[0][1].column_clip_;

        }

        //cot 2
        p_column[1][0].Show(g_render,column_rect[1][0]);
        p_column[1][1].Show(g_render,column_rect[1][1]);
        p_column[1][0].Column_Run();
        p_column[1][1].Column_Run();
        if( p_column[1][0].x_pos_ == - COLUMN_WIDTH)
        {
            p_column[1][0].Set_Column_Clip(p_column[0][0].x_pos_ + COLUMN_DISTANCE - COLUMN_WIDTH,
                                           0,
                                           COLUMN_WIDTH,
                                           rand() % 380 + 50);
            column_rect[1][0] = p_column[1][0].column_clip_;


            p_column[1][1].Set_Column_Clip(p_column[1][0].column_clip_.x,
                                           p_column[1][0].column_clip_.h + COLUMN_BLANK,
                                           COLUMN_WIDTH,
                                           SCREEN_HEIGHT - p_column[1][0].column_clip_.h - COLUMN_BLANK);
            column_rect[1][1] = p_column[1][1].column_clip_;

        }

        //cot 3
        p_column[2][0].Show(g_render,column_rect[2][0]);
        p_column[2][1].Show(g_render,column_rect[2][1]);
        p_column[2][0].Column_Run();
        p_column[2][1].Column_Run();
        if( p_column[2][0].x_pos_ == - COLUMN_WIDTH)
        {
            p_column[2][0].Set_Column_Clip(p_column[1][0].x_pos_ + COLUMN_DISTANCE - COLUMN_WIDTH,
                                           0,
                                           COLUMN_WIDTH,
                                           rand() % 380 + 50);
            column_rect[2][0] = p_column[2][0].column_clip_;


            p_column[2][1].Set_Column_Clip(p_column[2][0].column_clip_.x,
                                           p_column[2][0].column_clip_.h + COLUMN_BLANK,
                                           COLUMN_WIDTH,
                                           SCREEN_HEIGHT - p_column[2][0].column_clip_.h - COLUMN_BLANK);
            column_rect[2][1] = p_column[2][1].column_clip_;

        }

        //cot 4
        p_column[3][0].Show(g_render,column_rect[3][0]);
        p_column[3][1].Show(g_render,column_rect[3][1]);
        p_column[3][0].Column_Run();
        p_column[3][1].Column_Run();
        if( p_column[3][0].x_pos_ == - COLUMN_WIDTH)
        {
            p_column[3][0].Set_Column_Clip(p_column[2][0].x_pos_ + COLUMN_DISTANCE - COLUMN_WIDTH,
                                           0,
                                           COLUMN_WIDTH,
                                           rand() % 380 + 50);
            column_rect[3][0] = p_column[3][0].column_clip_;


            p_column[3][1].Set_Column_Clip(p_column[3][0].column_clip_.x,
                                           p_column[3][0].column_clip_.h + COLUMN_BLANK,
                                           COLUMN_WIDTH,
                                           SCREEN_HEIGHT - p_column[3][0].column_clip_.h - COLUMN_BLANK);
            column_rect[3][1] = p_column[3][1].column_clip_;

        }

        for(int i=0; i<4; i++)
        {
            for(int x = 0; x<2; x++)
            {
                score_ = Check_Score(p_column[i][x].renderQuad_1, &p_player.renderQuad, score_,Hit);
            }


        }


        //Show game score
        string str_score = "SCORE: ";
        Uint32 score_val = score_  ;

        string str_val = to_string(score_val);
        str_score += str_val;

        score_game.SetText(str_score);
        score_game.LoadFromRenderText(font_score,g_render);
        score_game.RenderText(g_render,SCREEN_WIDTH -200 , 15);




        SDL_RenderPresent(g_render);

        for(int i=0; i<4; i++)
        {
            for(int x = 0; x<2; x++)
            {
                if(Check_Va_Cham( p_column[i][x].renderQuad_1, &p_player.renderQuad ))
                {
                    is_gameover = true;
                    Mix_PlayChannel(-1,Ting, 0);
                    if(p_player.renderQuad.y + BIRD_HIGHT  <= SCREEN_HEIGHT)
                    {
                        column_rect[i][0].h = 0;
                        column_rect[i][1].y = SCREEN_HEIGHT;
                    }

                    p_player.y_pos_ = 200;
                    p_player.speed_ = 0;

                    break;
                }
            }
            if(is_gameover) break;
        }

        if(is_gameover)
        {
            Mix_HaltMusic(); // dung nhac nen
            Sleep(500);
            int ret_menu_over = ShowMenuGameOver(font_score, str_score);
            if(ret_menu_over == 1)
            {
                is_quit = true;
            }
            else if (ret_menu_over == 0)
            {
                score_ = 0;
                p_player.input_type_.up_ = 0;


                is_gameover = false;
                break;
            }
        }

        // SET_FPS
        if ((1000/FPS) > FPS_Timer.get_ticks()) //tg chay 1 frame CT
        {
            SDL_Delay((1000/FPS) - FPS_Timer.get_ticks());
        }

    }
}
    close();

    return 0;
}
