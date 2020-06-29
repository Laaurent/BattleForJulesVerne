#ifndef tir_h
#define tir_h

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "window.h"
#include "carte.h"

typedef struct tir_t{
    SDL_Texture *tex;
    SDL_Surface *surf;
    SDL_Rect hb;

    int dx, dy;
    int vit;
    uint32_t dst;
    int shot;
    int knockback;
}tir;

void tirer(tir*, SDL_Window**, SDL_Renderer**);
void destroyShot(tir*);

#endif /* tir_h */


