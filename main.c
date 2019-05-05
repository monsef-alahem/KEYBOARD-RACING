/*************************************
 *  KEYBOAR RACING
 *  AUTHOR  :   alahem monsef
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   __
 *  DATE    :   24-avril-2019
 *
 *************************************/


//utiliser sdl2
#include <SDL2/SDL.h>

//ouvrir des images a part bmp avec sdl2
#include <SDL2/SDL_image.h>

//lire sons et musiques avec sdl2
#include <SDL2/SDL_mixer.h>

//afficher du text avec sdl2
#include <SDL2/SDL_ttf.h>

#include <string.h>
#include <stdio.h>


///fin des headers


//variables globales

int i = 0;
int ret = 0;
int coins_left = 7;
int idx = 0;
int level_id = 0;


//variables globales SDL2
SDL_Window* window;
SDL_Renderer* renderer;
Mix_Chunk *wave;
Mix_Music *music;
SDL_Event event;
#define KEYS 28
typedef struct key_t{
    char letter;
    SDL_Keycode code; 
}key_t;


char level_text[1000][50];

void load_data()
{
    FILE *data_file = fopen("data.txt", "r");

    char prev_chr;
    int line_idx,i,j;
    int chr_idx = 0;
    i = j = 0;
    while(1)
    {
        level_text[j][i] = getc(data_file);
        if(level_text[j][i] == '\n' && prev_chr == '\n') {
            level_text[j][i] = getc(data_file);
        }
        if (i > 49) {
            printf("error line %d is too long\n", line_idx);
            goto error;
        }
        if (level_text[j][i] == EOF) {
            level_text[j][i] = 0;
            break;
        }

        prev_chr = level_text[j][i];

        if (level_text[j][i] == '\n') {
            level_text[j][i] = 0;
            line_idx += 1;
            j++;
            i = -1;
        }
        i++;
    }

    //rewind (data_file);
    //fseek (data_file , 0 , SEEK_SET);
    error:
    fclose(data_file);
}

#include "ui.h"

key_t key_table[KEYS] ={
    {'a',SDLK_a},
    {'b',SDLK_b},
    {'c',SDLK_c},
    {'d',SDLK_d},
    {'e',SDLK_e},
    {'f',SDLK_f},
    {'g',SDLK_g},
    {'h',SDLK_h},
    {'i',SDLK_i},
    {'j',SDLK_j},
    {'k',SDLK_k},
    {'l',SDLK_l},
    {'m',SDLK_m},
    {'n',SDLK_n},
    {'o',SDLK_o},
    {'p',SDLK_p},
    {'q',SDLK_q},
    {'r',SDLK_r},
    {'s',SDLK_s},
    {'t',SDLK_t},
    {'u',SDLK_u},
    {'v',SDLK_v},
    {'w',SDLK_w},
    {'x',SDLK_x},
    {'y',SDLK_y},
    {'z',SDLK_z},
    {'e',SDLK_2},
    {' ',SDLK_SPACE}

};

int answer_check() {
    ret = strcmp(input_box.text[0], quiz_box.text[0]);
    if (ret == 0) {
        idx++;
        wave = Mix_LoadWAV("good.mp3");
        Mix_PlayChannel(-1, wave, 0);
        strcpy(quiz_box.text[0], level_text[idx]);
        if (time_bar.w > 400)
            level_id += 5;
        if (time_bar.w > 300)
            level_id += 1;
        time_bar.w = 610;
        time_checkpoint = SDL_GetTicks();
    } else { 
        wave = Mix_LoadWAV("bad.mp3");
        Mix_PlayChannel(-1, wave, 0);
        coins_left--;
        time_bar.w = 610;
        time_checkpoint = SDL_GetTicks();
    }
    
    if (strcmp(level_text[idx], "fin du niveau") == 0) {
        wave = Mix_LoadWAV("level_up.mp3");
        Mix_PlayChannel(-1, wave, 0);
        idx++;
        level_id++;
        strcpy(quiz_box.text[0], level_text[idx]);
        SDL_Delay(300);
        time_bar.w = 610;
        time_checkpoint = SDL_GetTicks();
    }
}


int main(int argc, char**args)
{
    load_data();
    //demmarer sdl2
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

    //initialiser l'affichage du texte et choix police
    TTF_Init();

    //initialiser audio
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );

    //contruire une fenêtre
    window = SDL_CreateWindow( "KEYBOARD RACING", 500, 300, 640, 480, 0 );
    Uint32 flag = 0;
    SDL_SetWindowFullscreen(window, flag);

    //création de l'ecran de dessin dans la fenêtre
    renderer = SDL_CreateRenderer( window, -1, 0 );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    //ouvrir un fichier son ou musique
    //music = Mix_LoadMUS("under_moon.ogg");

    //jouer son et musique
    //Mix_PlayMusic( music, -1);
    //Mix_PlayChannel(-1, wave, 0);

    init_ui();
    

    int loop = 1;
    int i = 0;
    int ret = 0;

    while ( loop )
    {
        //efface l'ecran de dessin avec le noir (r,v,b,a) a = alpha la transparence
        SDL_SetRenderDrawColor( renderer,0,0,0,255);
        SDL_RenderClear( renderer );

        //entrée de clavier
        while ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_QUIT) {                
                    loop = 0;
            } else if ( event.type == SDL_KEYDOWN ) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    loop = 0;
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
/*                  static int once = 1;
                    if (!once)
                    {
                        input_box_clean_lines();
                        once = 1;
                    } else { */
                    answer_check();
                    input_box_clean_lines();
                    //}
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    input_box.cursor_pos--;
                    input_box.text[input_box.line_pos][input_box.cursor_pos] = 0;
                }

                if (event.key.keysym.sym == SDLK_DELETE) {
                    input_box_clean_lines();
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
/*                    if (input_box.line_pos < 2){        
                        input_box.cursor_pos = input_box.line_pos*50;
                        input_box.line_pos++;
                    }*/
                }

                for (i = 0 ; i < KEYS ; i++) {
                    if (event.key.keysym.sym == key_table[i].code) {
    /*                  static int once = 1;
                        if (!once) {
                            input_box_clean_lines();
                            once = 1;
                        }*/
                        input_box_append_letter(key_table[i].letter);
                        wave = Mix_LoadWAV("key.mp3");
                        Mix_PlayChannel(-1, wave, 0);

                    }
                }


            }
        }

        update_ui();
        if (coins_left == 0)
            loop = 0;

        draw_ui();

        //affiche l'ecran de dessin sur la fenetre
        SDL_RenderPresent(renderer);

        //pause x millisecondes avant de recommencer la boucle "while"
        SDL_Delay(32);
    }

    loop = 1;
    int w,h;
    char text[20];
    
    //update le level indicator
    SDL_Color text_color = {25,0,255};
    if (level_id < 10)
        sprintf(text, "ton level est %d, vise mieux", level_id);
    else if (level_id < 20)
        sprintf(text, "ton level est %d, tu peux faire mieux", level_id);
    else if (level_id < 30)
        sprintf(text, "ton level est %d, bien", level_id);
    else if (level_id < 40)
        sprintf(text, "ton level est %d, tu es rapide !", level_id);
    else if (level_id > 50)
        sprintf(text, "ton level est %d, tu es tres rapide !!!", level_id);

    hud_sur = TTF_RenderText_Solid(hud_font, text, text_color);
    hud_tex = SDL_CreateTextureFromSurface(renderer, hud_sur);
    SDL_QueryTexture(hud_tex, NULL, NULL, &w, &h);
    hud_rec.w = w;
    hud_rec.h = h;
    hud_rec = (SDL_Rect){(640/2)-(w/2),(480/2)-(h/2),w,h};


    while(loop) {
             //entrée de clavier
        while ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_QUIT) {                
                    loop = 0;
            } else if ( event.type == SDL_KEYDOWN ) {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        loop = 0;
            }
        }
        SDL_SetRenderDrawColor( renderer,0,0,0,255);
        SDL_RenderClear( renderer );


        //dessiner le level indicator
        SDL_RenderCopy(renderer, hud_tex, NULL, &hud_rec);

        SDL_RenderPresent(renderer);
        SDL_Delay(32);
    }

    //quand on quitte le programme (la boucle while) on detruit ce qu'on a crée
    //pour éviter les fuites de mémoire sur l'ordinateur
    Mix_FreeChunk(wave);
    Mix_FreeMusic(music);
    free_ui();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

}