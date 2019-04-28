/*************************************
 *  KEYBOAR RACING
 *  AUTHOR  :   alahem monsef
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   __
 *  DATE    :   24-avril-2019
 *
 *************************************/

//time
SDL_Rect time_bar = {15,320,610,10};
double time_checkpoint = 0;

//level indicator
TTF_Font* hud_font;
SDL_Surface* hud_sur;
SDL_Texture* hud_tex;
SDL_Rect hud_rec = {530,10,0,0};

//coins
SDL_Texture* coin_tex;
SDL_Surface* coin_sur;

//title


int init_hud()
{
    hud_font = TTF_OpenFont("arial.ttf", 25);

    //coins
    coin_sur = IMG_Load("coin.png");
    Uint32 colorkey = SDL_MapRGB(coin_sur->format, 0, 255, 0);
    SDL_SetColorKey(coin_sur, SDL_TRUE, colorkey);
    coin_tex = SDL_CreateTextureFromSurface(renderer, coin_sur);
}

int update_hud()
{
    //level indicator
    int w,h;
    static char text[20]; 
    SDL_Color text_color = {25,0,255};
    sprintf(text, "level : %d", level_id);
    hud_sur = TTF_RenderText_Solid(hud_font, text, text_color);
    hud_tex = SDL_CreateTextureFromSurface(renderer, hud_sur);
    SDL_QueryTexture(hud_tex, NULL, NULL, &w, &h);
    hud_rec.w = w;
    hud_rec.h = h;

    //time
    if (SDL_GetTicks() - time_checkpoint > 100) {
        int x = (int)((level_id+1)*3/strlen(level_text[idx]));
        if(x == 0)
            x = 1;
        time_bar.w-=x;
        time_checkpoint = SDL_GetTicks();
    }

    if (time_bar.w < 0) {      
        wave = Mix_LoadWAV("bad.mp3");
        Mix_PlayChannel(-1, wave, 0);
        coins_left--;
        time_bar.w = 610;
        time_checkpoint = SDL_GetTicks();
    }
}

int draw_hud()
{
    //time bar
    SDL_Color bar_col = {255,255,0,255};
    SDL_SetRenderDrawColor( renderer,bar_col.r,bar_col.g,bar_col.b,bar_col.a); 
    SDL_RenderFillRect( renderer, &time_bar);

    //level indicator text
    SDL_RenderCopy(renderer, hud_tex, NULL, &hud_rec);

    //coin
    int w,h,i;
    SDL_QueryTexture(coin_tex, NULL, NULL, &w, &h);
    for (i=0 ; i<coins_left ; i++)
        SDL_RenderCopy(renderer, coin_tex, &(SDL_Rect){0,0,w,h}, &(SDL_Rect){20+(i*25),13,w,h});

}
int free_hud()
{
    //hud
    SDL_DestroyTexture(hud_tex);
    SDL_FreeSurface(hud_sur);
    
    //coin
    SDL_DestroyTexture(coin_tex);
    SDL_FreeSurface(coin_sur);

    TTF_CloseFont(hud_font);
}