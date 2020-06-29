#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "window.h"
#include "perso.h"
#include "menu.h"
#include "bouton.h"
#include "jeu.h"

int main(int argc, char *argv[])
{

    // -- VARIABLES DE FENETRE --
    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;

    // -- AUTRES VARIABLES --
    int *loop = malloc(sizeof(int));
    *loop = 1;
    SDL_Event event;

    // Cree la fenetre et le rendu
    if(initWindow(&win, &ren) != 0)
        QuitError("Fenetre et rendu non crees");

    // ICONE DE LA FENETRE
    SDL_Surface* icone;
    icone = IMG_Load("./images/LOGO_SQUARE.png");
    SDL_SetWindowIcon(win, icone);

    // BACKGROUND ET LOGO DU MENU PRINCIPAL
    menu menu_bg, menu_logo,menu_sprite;
    initImageMenu(&menu_bg, "./images/menu.png", &ren, &win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,0);
    initImageMenu(&menu_logo, "./images/logo.png", &ren, &win, 550, 100,0 ,0,1.5 );
    initImageMenu(&menu_sprite, "./images/SPRITE_PROJET_DROITE.png", &ren, &win,150,200 ,200,200,1 );

    SDL_Rect bande_noire;
    initRectangle(&bande_noire,&ren,0,0,500,SCREEN_HEIGHT,0,0,0,128);

    // GESTION DES ANIMATIONS DES SPRITES
    Uint32 sprite = 0;

    // Perso principal
    perso p;
    creerPerso(&p, &win, &ren);

    // BOUTON
    bouton NEW,QUIT;
    creerBouton(&NEW,"./images/BOUTON_NOUVELLE_PARTIE.png","./images/BOUTON_NOUVELLE_PARTIE_SURVOLE.png", &win, &ren, bande_noire.w/2 - 400/2, 450, 1);
    creerBouton(&QUIT,"./images/BOUTON_QUITTER.png","./images/BOUTON_QUITTER_SURVOLE.png", &win, &ren, bande_noire.w/2 - 400/2, 530, 1);

    // Change le curseur
    SDL_Cursor *curs_ptr = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_Cursor *curs_clic = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(curs_ptr);

    int souris_x,souris_y;

    /* MUSIQUE DU MENU */
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0 )
        QuitErrorWR((char*)Mix_GetError(), &win, &ren);
    Mix_Music *menumus = Mix_LoadMUS("./sounds/Menu.wav");

    // Boucle principale du jeu
    while(*loop)
    {
        // DELAY
        SDL_Delay(16);

        if(!Mix_PlayingMusic())
            Mix_PlayMusic(menumus, 1);

        // ANIMATION DES SPRITES
        sprite = SDL_GetTicks() / 100 % 6; // QUAND 6 SPRITES
        SDL_Rect srcrect = { sprite * 100, 0, 100, 600 };// QUAND 6 SPRITES

        SDL_GetMouseState(&souris_x,&souris_y);

        // GESTION DES EVENEMENTS
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                {
                    // SI ON SURVOLE LE BOUTON
                    hitboxBouton(&NEW, curs_clic, souris_x, souris_y);
                    hitboxBouton(&QUIT, curs_clic, souris_x, souris_y);
                }break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    if(hitboxBouton(&NEW, curs_clic, souris_x, souris_y)){
                        Mix_CloseAudio();
                        SDL_SetCursor(curs_ptr);
                        SDL_Delay(100);
                        jouer(&loop,&ren,&win);
                    }
                    if(hitboxBouton(&QUIT, curs_clic, souris_x, souris_y)) *loop = 0;
                }break;
                case SDL_QUIT:
                    *loop = 0;
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(ren);
        // Place l'image sur la fenÍtre
        SDL_RenderCopy(ren, menu_bg.tex, NULL, &menu_bg.pos);
        //Render bande noire du menu
        SDL_RenderFillRect(ren,&bande_noire);
        // AFFICHAGE LOGO
        SDL_RenderCopy(ren, menu_logo.tex, NULL, &menu_logo.pos);
        // AFFICHAGE SPRITE MENU
        SDL_RenderCopy(ren, menu_sprite.tex, &srcrect, &menu_sprite.pos);
        // AFFICHAGE BOUTONS
        affichageBouton(&NEW, &ren);
        affichageBouton(&QUIT, &ren);
        // afichage de toutes les images
        SDL_RenderPresent(ren);

    }

    free(loop);
    free(menumus);
    SDL_FreeCursor(curs_ptr);
    SDL_FreeCursor(curs_clic);
    Mix_CloseAudio();
    TTF_Quit();
    freeMem(&win, &ren);
    return 0;
}

