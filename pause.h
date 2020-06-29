#ifndef pause_h
#define pause_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "bouton.h"

enum Menu {PAUSE, WIN, LOSE};

void menuPause(SDL_Renderer**,SDL_Window**,int**, int*, int);

#endif /* pause_h */
