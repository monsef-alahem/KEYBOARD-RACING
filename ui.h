/*************************************
 *  input_box SDL2
 *  KEYBOAR RACING
 *  AUTHOR  :   alahem monsef
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   __
 *  DATE    :   24-avril-2019
 *
 *************************************/

typedef struct rgba_t {
    int r;
    int g;
    int b;
    int a;
}rgba_t;

typedef struct text_line_t {
    SDL_Surface* sur;
    SDL_Texture* tex;
    SDL_Rect rec;
}text_line_t;

#include "input_box.h"
#include "quiz_box.h"
#include "hud.h"

void init_ui()
{
    init_input_box();
    init_quiz_box();
    init_hud();
}

void update_ui()
{
    update_input_box();
    update_quiz_box();
    update_hud();
}

void draw_ui()
{
    draw_input_box();
    draw_quiz_box();
    draw_hud();
}

int free_ui()
{
    free_input_box();
    free_quiz_box();
    free_hud();
}