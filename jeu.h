#ifndef jeu_h
#define jeu_h

#define FPS_LIMIT 16 /* 60 fps : 1000/60 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "perso.h"
#include "window.h"
#include "tir.h"
#include "pause.h"
#include "carte.h"
#include "font.h"

void fpsLimit(unsigned int);
void jouer(int**,SDL_Renderer**,SDL_Window**);

#endif /* jeu_h */

