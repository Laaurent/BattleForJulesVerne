#include "carte.h"

void LoadMap(map *m,char* path){
    int pos,posrectx,posrecty;
    char c;
    posrectx = 0;
    posrecty = 0;
    pos = -1;

    tile tileTemp;
    tileTemp.num = ' ';
    tileTemp.tex = NULL;
    tileTemp.pos.x = 0;
    tileTemp.pos.y = 0;
    tileTemp.pos.w = tileTemp.pos.h = 100;

    FILE *Fmap = NULL;
    Fmap = fopen(path, "r+");

    do{
        c = fgetc(Fmap);
        if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == 'a' || c == 'b') {
            pos++;
            m->tiletab[pos].num = c;
            if (pos % 12 == 0 && pos > 0) {
                posrectx = 0;
                posrecty ++;
            }
            m->tiletab[pos].pos.x = posrectx * 100;
            m->tiletab[pos].pos.y = posrecty * 100;
            posrectx++;
            //printf("(%d,%d,%d)",pos,m->tiletab[pos].pos.x,m->tiletab[pos].pos.y);
        }


    }while (c != EOF);

    fclose(Fmap);
    free(Fmap);
}

void InitMap(map *m,SDL_Renderer* ren, SDL_Window *win){
    for (int i = 0; i < 84; i++) {
        switch (m->tiletab[i].num) {
            case '0':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/0.png", &ren, &win); // sol gris
            }break;
            case '1':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/1.png", &ren, &win); // mur haut
            }break;
            case '2':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/2.png", &ren, &win); // mur bas
            }break;
            case '3':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/3.png", &ren, &win); // porte fermee
            }break;
            case '4':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/4.png", &ren, &win); // trou
            }break;
            case '5':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/5.png", &ren, &win); // mur droite
            }break;
            case '6':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/6.png", &ren, &win); // mur gauche
            }break;
            case '7':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/7.png", &ren, &win); // coin bas-gauche
            }break;
            case '8':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/8.png", &ren, &win); // coin haut-gauche
            }break;
            case '9':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/9.png", &ren, &win); // coin haut-droite
            }break;
            case 'a':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/a.png", &ren, &win); // coin bas-droite
            }break;
            case 'b':
            {
                initTile(&m->tiletab[i], "./map/tile_map1/b.png", &ren, &win); // porte cote
            }break;


            default:
                initTile(&m->tiletab[i], "./images/tile2.png", &ren, &win);
                break;

        }

    }
}

void initTile(tile *t,char *path,SDL_Renderer** ren,SDL_Window **win){
    loadIMG(path, &t->surf, &t->tex, win, ren);
    if(SDL_QueryTexture(t->tex, NULL, NULL, &t->pos.w, &t->pos.h) != 0)
        QuitErrorWR("tile non creee", win ,ren);
}

void DrawMap(map *m,SDL_Renderer *ren){
    for (int i = 0; i < 84; i++) {
        if (m->tiletab[i].tex != NULL) {
            SDL_RenderCopy(ren, m->tiletab[i].tex, NULL, &m->tiletab[i].pos);
        }
    }
}



