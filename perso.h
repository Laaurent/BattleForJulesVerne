#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define FPS_LIMIT 16 /* 60 fps : 1000/60 */

#ifndef perso_h
#define perso_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "window.h"
#include "carte.h"
#include "tir.h"
#include "font.h"

// Perso princpal
typedef struct perso_t{
    SDL_Texture *tex,*tex_immo, *tex_haut, *tex_bas, *tex_droite, *tex_gauche;
    font *popup;
    SDL_Surface *surf;
    SDL_Rect hb;

    //vitesse, point de vie, point de vie max, attaque, nombre de tir
    //frequence de tir, temps d'invulnerabilite, direction de mouvement
    int spd, pdv, pdvMax, atk, nTir, money, cdTir, invFrm, droite, gauche, haut, bas;
    tir **shot;
    uint32_t prevTirTick;
    uint32_t prevDmgTick; // frame touchee

}perso;

// barre de vie
typedef struct healthbar_t{
    SDL_Texture *tBarre, *tHud;
    SDL_Surface *surf, *surf2;
    SDL_Rect     rBarre, rBarreMod, rHud;

    float pourcent;
    int len;
}healthbar;

void creerPerso(perso*, SDL_Window**, SDL_Renderer**);
void creerEnnemi(perso*, SDL_Window**, SDL_Renderer**);
void chgEnnemi(perso*, int, int, int, int, int, int, SDL_Window**, SDL_Renderer**);
void creerTir(tir*,perso*, int, int, SDL_Window**, SDL_Renderer**);
void eBlindMoves(perso*, map*,SDL_Window**, SDL_Renderer**);
void eTposeMoves(perso*, int,int, map*, SDL_Window**, SDL_Renderer**);
void persoMove(perso*, map*);
int collision(map*, perso*);
void porteCol(perso*, perso e[3], map*, int*,char* path[6], SDL_Window**, SDL_Renderer**);
void charCol(perso*, perso e[3],SDL_Window**, SDL_Renderer**);
void tirCol(tir*, perso*, perso*, font*, SDL_Window**, SDL_Renderer**);
void tirKnockback(int, int, int, int*, int*, int*, int*, SDL_Rect*);
void loadRoom(perso e[3], perso*, int, SDL_Window**, SDL_Renderer**);
void updateRoom(perso e[3],perso*, map*, int, SDL_Rect*, font*, uint32_t, SDL_Window**, SDL_Renderer**);
void pDmg(perso*, int, SDL_Window**, SDL_Renderer**);
void destroyPerso(perso*);
void createHealthbar(healthbar*, SDL_Window**, SDL_Renderer**);
void updateHealthbar(healthbar*, int, int);
void updatePerso(perso*, SDL_Rect, uint32_t, SDL_Window**, SDL_Renderer**);

#endif /* perso_h */
