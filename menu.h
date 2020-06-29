#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#ifndef menu_h
#define menu_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "window.h"

// Image de fond
typedef struct menu_t{
    SDL_Texture *tex;
    SDL_Surface *surf;
    SDL_Rect pos;
}menu;

void initImageMenu(menu *,char *,SDL_Renderer** ,SDL_Window **,int ,int ,int , int,float );
void initRectangle(SDL_Rect* ,SDL_Renderer**,int , int , int , int , int , int , int , int );

#endif /* menu_h */
