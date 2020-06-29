#include "pause.h"

void menuPause(SDL_Renderer **ren,SDL_Window** win,int **loop, int *jouerLoop, int i){
    int p = 1;

    SDL_Event event;

    menu menu_pause;
    char* path = NULL;
    switch(i)
    {
        case 0: path = "./images/MENU_PAUSE.png";
        break;

        case 1: path = "./images/MENU-VICTOIRE.png";
        break;

        case 2: path = "./images/MENU-DEFAITE.png";
        break;
    }
    initImageMenu(&menu_pause, path, ren, win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,0);
    free(path);


    // BOUTON
    bouton CONTINUE,QUIT;
    creerBouton(&CONTINUE,"./images/BOUTON_CONTINUER.png","./images/BOUTON_CONTINUER_SURVOLE.png",win,ren, SCREEN_WIDTH/2 - 400/2 , 450, 1);
    creerBouton(&QUIT,"./images/BOUTON_QUITTER.png","./images/BOUTON_QUITTER_SURVOLE.png", win, ren, SCREEN_WIDTH/2 - 400/2 , 520, 1);

    // Curseurs
    SDL_Cursor *curs_ptr = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_Cursor *curs_clic = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    int souris_x,souris_y;

    while (p == 1) {

        SDL_GetMouseState(&souris_x,&souris_y);

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYUP:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            if(i==0)
                                p = 0;
                        break;
                    }
                }break;
                case SDL_MOUSEMOTION :
                {
                    // SI ON SURVOLE LE BOUTON
                    hitboxBouton(&CONTINUE, curs_clic, souris_x, souris_y);
                    hitboxBouton(&QUIT, curs_clic, souris_x, souris_y);
                    }break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    if(hitboxBouton(&CONTINUE, curs_clic, souris_x, souris_y)){
                        p = 0;
                        if(i!=0)
                            *jouerLoop = 0;
                    }
                    if(hitboxBouton(&QUIT, curs_clic, souris_x, souris_y)){
                        p = 0;
                        *jouerLoop = 0;
                        **loop = 0;
                    }
                }break;
                case SDL_QUIT:
                    p = 0;
                    **loop = 0;
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(*ren);
        SDL_RenderCopy(*ren, menu_pause.tex, NULL, &menu_pause.pos);
        affichageBouton(&CONTINUE, ren);
        affichageBouton(&QUIT, ren);
        SDL_RenderPresent(*ren);
    }
    SDL_SetCursor(curs_ptr);
    free(curs_clic);
    free(curs_ptr);
}
