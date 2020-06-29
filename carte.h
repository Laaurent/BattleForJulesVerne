#ifndef carte_h
#define carte_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <ctype.h>

#include "menu.h"
#include "window.h"

typedef struct tile_t{
    char num;
    SDL_Texture *tex;
    SDL_Surface *surf;
    SDL_Rect pos;
}tile;

typedef struct map_t{
    tile tiletab[84];
}map;

void LoadMap(map*,char*);
void InitMap(map *,SDL_Renderer* , SDL_Window *);
void initTile(tile *,char *,SDL_Renderer** ,SDL_Window **);
void DrawMap(map *,SDL_Renderer *);

#endif /* carte_h */
