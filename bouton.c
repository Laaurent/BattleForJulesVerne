#include "bouton.h"

void creerBouton(bouton *b,char* path,char* path2,SDL_Window **win, SDL_Renderer **ren,int x,int y, float w)
{
    loadIMG(path, &b->surf, &b->tex, win, ren);
    if(SDL_QueryTexture(b->tex, NULL, NULL, &b->pos.w, &b->pos.h) != 0)
        QuitErrorWR("Image de fond du bouton non creee", win ,ren);
    loadIMG(path2, &b->surf, &b->tex_survol, win, ren);
    if(SDL_QueryTexture(b->tex, NULL, NULL, &b->pos.w, &b->pos.h) != 0)
        QuitErrorWR("Image de fond du bouton survol non creee", win ,ren);
    b->pos.x = x;
    b->pos.y = y;
    b->pos.w /= w;
    b->pos.h /= w;
    b->survole = 0;
}

int hitboxBouton(bouton* b, SDL_Cursor *curs_clic, int souris_x, int souris_y){
    if(souris_x>b->pos.x && souris_x<b->pos.x+b->pos.w && souris_y>b->pos.y && souris_y<b->pos.y+b->pos.h){
        SDL_SetCursor(curs_clic);
        b->survole = 1;
        return 1;
    }
    else{
        SDL_SetCursor(curs_clic);
        b->survole = 0;
        return 0;
    }
}

void affichageBouton(bouton *b,SDL_Renderer **ren){
    if (b->survole == 1) {
        SDL_RenderCopy(*ren, b->tex_survol, NULL, &b->pos);
    }
    else
    {
        SDL_RenderCopy(*ren, b->tex, NULL, &b->pos);
    }
}
