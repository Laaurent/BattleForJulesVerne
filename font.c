#include "font.h"

SDL_Color setColor(int i){
    SDL_Color c;
    switch(i){
        case 0:
            c.r = 0;
            c.g = 0;
            c.b = 0;
        break;

        case 1:
            c.r = 255;
            c.g = 255;
            c.b = 255;
        break;

        case 2:
            c.r = 140;
            c.g = 140;
            c.b = 140;
        break;

        case 3:
            c.r = 255;
            c.g = 53;
            c.b = 24;
        break;

        case 4:
            c.r = 77;
            c.g = 142;
            c.b = 232;
        break;

        case 5:
            c.r = 65;
            c.g = 195;
            c.b = 134;
        break;

        default:
        break;
    }
    return c;
}

// cree une police
void setTTF(font *police, int size, enum couleurs col, char* txt, int x, int y, int duree, SDL_Window **win, SDL_Renderer **ren){
    police->font = TTF_OpenFont("./ttf/Pixel.ttf", size);
    police->color = setColor((int)col);
    police->surf = TTF_RenderText_Solid(police->font, txt, police->color);
    police->tex = SDL_CreateTextureFromSurface(*ren, police->surf);
    SDL_FreeSurface(police->surf);

    if(SDL_QueryTexture(police->tex, NULL, NULL, &police->rect.w, &police->rect.h) != 0)
        QuitErrorWR("Creation de la police", win ,ren);
    police->rect.x = x;
    police->rect.y = y;

    police->duree = duree;
    police->poped = SDL_GetTicks();
}

// Cree l'image de l'argent
void createMoney(moneyHud *m, SDL_Window **win, SDL_Renderer **ren){
    loadIMG("./images/SPRITE_PROJET_ARGENT.png",&m->surf,&m->tex,win,ren);
    if(SDL_QueryTexture(m->tex, NULL, NULL, &m->rect.w, &m->rect.h) != 0)
        QuitErrorWR("Creation du hud de l'argent non cree", win ,ren);
    m->rect.x = 250;
    m->rect.y = 0;
}

void updateMoney(font *police, int *m, int add, SDL_Window **win, SDL_Renderer **ren){
    (*m)+=add;

    char arr[10];
    sprintf(arr, "%d",*m);
    police->surf = TTF_RenderText_Solid(police->font, arr, police->color);
    police->tex = SDL_CreateTextureFromSurface(*ren, police->surf);
    SDL_FreeSurface(police->surf);

    if(SDL_QueryTexture(police->tex, NULL, NULL, &police->rect.w, &police->rect.h) != 0)
        QuitErrorWR("Changement de la police echoue", win ,ren);
}
