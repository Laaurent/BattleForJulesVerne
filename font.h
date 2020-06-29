#ifndef font_h
#define font_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"

enum couleurs {NOIR, BLANC, GRIS, ROUGE, BLEU, VERT};

typedef struct font_t{
    TTF_Font *font;
    SDL_Texture *tex;
    SDL_Surface *surf;
    SDL_Rect rect;
    SDL_Color color;
    unsigned int duree;
    uint32_t poped;
}font;

typedef struct moneyHud_t{
    SDL_Texture *tex;
    SDL_Surface *surf;
    SDL_Rect    rect;
}moneyHud;

SDL_Color setColor(int);
void setTTF(font*, int, enum couleurs, char*, int, int, int, SDL_Window**, SDL_Renderer**);
void createMoney(moneyHud*, SDL_Window**, SDL_Renderer**);
void updateMoney(font*, int*, int, SDL_Window**, SDL_Renderer**);



#endif
