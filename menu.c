#include "menu.h"

void initImageMenu(menu *m,char *path,SDL_Renderer** ren,SDL_Window **win,int x,int y,int w, int h,float z){
    loadIMG(path, &m->surf, &m->tex, win, ren);
    if(SDL_QueryTexture(m->tex, NULL, NULL, &m->pos.w, &m->pos.h) != 0)
        QuitErrorWR("Menu non creee", win ,ren);
    m->pos.x = x;
    m->pos.y = y;
    if (w == 0 && h == 0) {
        m->pos.w /= z;
        m->pos.h /= z;
    }
    else{
        m->pos.w = w;
        m->pos.h = h;
    }
}

void initRectangle(SDL_Rect *rec,SDL_Renderer** ren,int x, int y, int w, int h, int r, int g, int b, int a)
{
    rec->x = x;
    rec->y = y;
    rec->w = w;
    rec->h = h;
    SDL_SetRenderDrawBlendMode(*ren,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(*ren, r, g, b, a);
}

