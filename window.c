#include "window.h"

// Quitte avec un message d'erreur et ferme la SDL
void QuitError(char *err)
{
    SDL_Log("Erreur : %s -> %s \n", err, SDL_GetError());
    SDL_Quit();
    Mix_Quit();
    exit(EXIT_FAILURE);
}

// Idem, mais utilise apres avoir cree la fenetre et le rendu
void QuitErrorWR(char *err, SDL_Window **win, SDL_Renderer **ren){
    SDL_DestroyRenderer(*ren);
    SDL_DestroyWindow(*win);
    QuitError(err);
}

// Initialise la fenetre et le rendu
int initWindow(SDL_Window **win, SDL_Renderer **ren){

     // Initialisation de la SDL
    if(TTF_Init() != 0)
        QuitError("Initialisation TTF");
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        QuitError("Initialisation SDL");
    else
    {
        // Creation de la fenetre
        *win =  SDL_CreateWindow("ALL STAR UPJV",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN );
        if(*win == NULL)
        {
            QuitError("Création de la fenêtre");
            return 1;
        }

        // Creation du rendu
        *ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);
        if(*ren == NULL)
        {
            QuitError("Creation renderer echouee");
            return 1;
        }
    }
    return 0;
}

// Charge une image grace a sa surface
// Lui applique une texture et libere la surface
void *loadIMG(char *chemin, SDL_Surface **surf, SDL_Texture **tex, SDL_Window **win, SDL_Renderer **ren){
    *surf = IMG_Load(chemin);
    if(*surf == NULL)
        QuitErrorWR("Image non chargee", win, ren);

    *tex = SDL_CreateTextureFromSurface(*ren, *surf);
    SDL_FreeSurface(*surf);
    *surf = NULL;
    if(*tex == NULL)
        QuitErrorWR("Texture non chargee", win, ren);
}

void freeMem(SDL_Window **win, SDL_Renderer **ren){

    SDL_DestroyRenderer(*ren);
    SDL_DestroyWindow(*win);
    Mix_Quit();
    SDL_Quit();
}



