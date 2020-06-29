#ifndef bouton_h
#define bouton_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "window.h"

//BOUTON
typedef struct bouton_t{
    SDL_Texture *tex;
    SDL_Texture *tex_survol;
    SDL_Surface *surf;
    SDL_Rect pos;
    int survole;
}bouton;

void creerBouton(bouton*,char*,char*,SDL_Window**, SDL_Renderer**,int,int, float);
int hitboxBouton(bouton*,SDL_Cursor*,int, int);
void affichageBouton(bouton *,SDL_Renderer**);


#endif /* bouton_h */
