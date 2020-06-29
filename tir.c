#include "tir.h"

// donne un vecteur de mouvement au tir
void tirer(tir *t, SDL_Window** win, SDL_Renderer** ren){
    t->hb.x += (t->dx / sqrt(t->dx*t->dx + t->dy*t->dy)) *t->vit;
    t->hb.y += (t->dy / sqrt(t->dx*t->dx + t->dy*t->dy)) *t->vit;
}

// Detruit les tirs
void destroyShot(tir *t){
    t->shot = 0;
    t->hb.x = -50;
    t->hb.y = -50;
}


