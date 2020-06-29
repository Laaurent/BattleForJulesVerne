#ifndef window_h
#define window_h

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

void QuitError(char*);
void QuitErrorWR(char*, SDL_Window**, SDL_Renderer**);
int initWindow(SDL_Window**, SDL_Renderer**);
void *loadIMG(char*, SDL_Surface**, SDL_Texture**, SDL_Window**, SDL_Renderer**);
void freeMem(SDL_Window**, SDL_Renderer**);

#endif /* window_h */

