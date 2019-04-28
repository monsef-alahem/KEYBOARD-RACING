/*************************************
 *  KEYBOAR RACING
 *  AUTHOR  :   alahem monsef
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   __
 *  DATE    :   24-avril-2019
 *
 *************************************/
#define INPUT_LINE_LEN 50
typedef struct text_box_t {
    rgba_t col;
    rgba_t brd_col;
    int brd_tick;
    SDL_Rect rec;
    char text[3][INPUT_LINE_LEN];
    text_line_t line[3];
    SDL_Rect txt_cursor;
    int cursor_pos;
    int line_pos;
    TTF_Font* font;
    int font_size;
}text_box_t;


//place to declare struct

text_box_t input_box = {
    {0,255,240,255},
    {0,255,100,255},
    10,
    {20,340,600,120},
    {"","",""},
    {
    NULL,NULL,{30,350,370,190},
    NULL,NULL,{30,350+30,370,190},
    NULL,NULL,{30,350+60,370,190}
    },
    {8,20,10,20},
    0,
    0,
    NULL,
    20
};

//utilities
int input_box_clean_lines()
{
    int i = 0;
    input_box.line_pos = 0;
    input_box.cursor_pos = 0;
    for (i=0;i<3;i++)
        memset(input_box.text[i],0,INPUT_LINE_LEN);
}

int input_box_append_letter(char c)
{
    if (input_box.line_pos < 2) {
        input_box.text[input_box.line_pos][input_box.cursor_pos] = c;
        input_box.cursor_pos++;
        if (input_box.cursor_pos == INPUT_LINE_LEN-1) {
            input_box.line_pos++;
            input_box.cursor_pos = 0;
            return;
        }
    }
    if (input_box.line_pos == 2) {
        input_box.text[input_box.line_pos][input_box.cursor_pos] = c;
        if (input_box.cursor_pos < INPUT_LINE_LEN-1)
            input_box.cursor_pos++;
    }
}



void init_input_box()
{
    input_box.font = TTF_OpenFont("arial.ttf", input_box.font_size);
    int i = 0;
    for (i=0;i<3;i++) {
        SDL_Color text_color = {0, 255, 240};
    }
}


void update_input_box()
{
    //update graphics
    int i,w,h = 0;

    for (i=0;i<3;i++) {
        SDL_Color text_color = {255,255,255};
        input_box.line[i].sur = TTF_RenderText_Solid(input_box.font, input_box.text[i], text_color);
        input_box.line[i].tex = SDL_CreateTextureFromSurface(renderer, input_box.line[i].sur);
        SDL_QueryTexture(input_box.line[i].tex, NULL, NULL, &w, &h);
        input_box.line[i].rec.w = w;
        input_box.line[i].rec.h = h;
    }

    //update cursor position
    input_box.txt_cursor.x = 30 + w;
    input_box.txt_cursor.y = 350 + input_box.line_pos*30;

    //correction of cursor pos bug
    if (input_box.cursor_pos == 0)
        input_box.txt_cursor.x = 10 + 30;

}

void draw_input_box()
{
    //draw border
    SDL_Rect border = {
        input_box.rec.x-input_box.brd_tick/2,
        input_box.rec.y-input_box.brd_tick/2,
        input_box.rec.w+input_box.brd_tick,
        input_box.rec.h+input_box.brd_tick};
    SDL_SetRenderDrawColor( renderer,255,255,0,120); 
    SDL_RenderFillRect( renderer, &border);
    
    //draw input box background rectangle
    SDL_SetRenderDrawColor( renderer,0,0,0,255); 
    SDL_RenderFillRect( renderer, &input_box.rec);

    //draw text
    SDL_SetRenderDrawColor( renderer,
        0,255,100,255
    ); 
    int i;
    for (i = 0;i<3;i++) {     
        SDL_RenderCopy(renderer, input_box.line[i].tex, NULL, (&input_box.line[i].rec));
    }

    if (SDL_GetTicks()/500 % 2 == 0) {
        SDL_SetRenderDrawColor( renderer,255,255,0,255); 
        SDL_RenderFillRect( renderer, &input_box.txt_cursor);
    }

}

void free_input_box()
{
    int i;
    for (i = 0;i < 3;i++) { 
        SDL_DestroyTexture(input_box.line[i].tex);
        SDL_FreeSurface(input_box.line[i].sur);
    }
    TTF_CloseFont(input_box.font);
}