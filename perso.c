#include "perso.h"

// Cree le perso
void creerPerso(perso *p, SDL_Window** win, SDL_Renderer** ren){
    /* SPRITES */
    loadIMG("./images/SPRITE_PROJET_IMMO.png", &p->surf, &p->tex, win, ren);
    loadIMG("./images/SPRITE_PROJET_IMMO.png", &p->surf, &p->tex_immo, win, ren);
    loadIMG("./images/SPRITE_PROJET_HAUT.png", &p->surf, &p->tex_haut, win, ren);
    loadIMG("./images/SPRITE_PROJET_BAS.png", &p->surf, &p->tex_bas, win, ren);
    loadIMG("./images/SPRITE_PROJET_DROITE.png", &p->surf, &p->tex_droite, win, ren);
    loadIMG("./images/SPRITE_PROJET_GAUCHE.png", &p->surf, &p->tex_gauche, win, ren);
    if(SDL_QueryTexture(p->tex, NULL, NULL, &p->hb.w, &p->hb.h) != 0)
        QuitErrorWR("Creation de la hitbox du perso non creee", win ,ren);

    /* HITBOX */
    p->hb.x = 200 ;
    p->hb.y = 200 ;
    p->hb.w = 100;
    p->hb.h = 100;

    /* DIRECTION */
    p->droite = p->gauche = p->haut = p->bas = 0;

    /* STATISTIQUES */
    p->spd = 5;
    p->pdvMax = 100;
    p->pdv = 100;
    p->atk = 5;
    p->money = 0;

    p->nTir = 1;
    p->cdTir = 500;
    p->prevTirTick = 0;
    p->shot = (tir**)malloc(sizeof(tir*));

    p->popup =(font*)malloc(sizeof(font));

    /* FRAME D'INVINCIBILITE */
    p->invFrm = 1000;
    p->prevDmgTick = 0;
}

// Cree un ennemi avec les statistiques donnes en parametres
void creerEnnemi(perso *p, SDL_Window** win, SDL_Renderer** ren){

    loadIMG("./images/SPRITE_PROJET_BLIND_GAUCHE.png", &p->surf, &p->tex_gauche, win, ren);
    loadIMG("./images/SPRITE_PROJET_BLIND_DROITE.png", &p->surf, &p->tex_droite, win, ren);
    loadIMG("./images/SPRITE_PROJET_TPOSE.png", &p->surf, &p->tex_immo, win, ren);


    p->droite = p->gauche = p->haut = p->bas = 0;
    p->nTir = 1;

    p->shot = (tir**)malloc(sizeof(tir*));
    p->shot[0] = (tir*)malloc(sizeof(tir));
    p->shot[0][0].vit = 10;
    loadIMG("./images/BALLE_CIRCLE.png", &p->shot[0][0].surf, &p->shot[0][0].tex, win, ren);

    p->hb.w = 100;
    p->hb.h = 100;

    p->popup =(font*)malloc(sizeof(font));

    p->cdTir = 2000;
    p->prevTirTick = SDL_GetTicks();

    p->invFrm = 200;
    p->prevDmgTick = 0;
}
void chgEnnemi(perso *p, int ennNo, int x, int y, int spd, int pdv, int atk, SDL_Window** win, SDL_Renderer** ren){

    if(ennNo == 0)
    {
        p->tex = p->tex_droite;
        p->droite = 1;
    }
    else if(ennNo == 1)
    {
        p->droite = p->gauche = 0;
        p->tex = p->tex_immo;
        p->prevTirTick = SDL_GetTicks();
    }
    p->hb.x = x;
    p->hb.y = y;

    p->spd = spd;
    p->pdv = pdv;
    p->pdvMax = pdv;
    p->atk = atk;

}
// Creation de tir
void creerTir(tir *t, perso *p, int souris_x, int souris_y, SDL_Window** win, SDL_Renderer** ren){
    uint32_t currTick = SDL_GetTicks();

    if(currTick - p->prevTirTick >= p->cdTir)
    {
        t[0].tex = p->shot[0][0].tex;
        if(SDL_QueryTexture(t[0].tex, NULL, NULL, &t[0].hb.w, &t[0].hb.h) != 0)
            QuitErrorWR("Creation de la hitbox du tir non creee", win ,ren);

        t[0].vit = 15;
        t[0].dst = currTick + 750;
        t[0].shot = 1;
        t[0].knockback = 10;

        // placer le tir sur le perso
        t[0].hb.x = p->hb.x + p->hb.w/2;
        t[0].hb.y = p->hb.y + p->hb.h/2;
        t[0].hb.w = 18;
        t[0].hb.h = 18;

        //vecteur de mouvement
        t[0].dx = souris_x - t[0].hb.x;
        t[0].dy = souris_y - t[0].hb.y;

        p->prevTirTick = currTick;
    }
}

// Gere le paterne de mouvement du perso "Blind"
// Accelere a chaque tiers de degat
// Fait des allers et retours
void eBlindMoves(perso *p, map *m, SDL_Window** win, SDL_Renderer **ren){
    int prevX = p->hb.x;
    int prevY = p->hb.y;

    float accel;
    if(p->pdv > 2*p->pdvMax/3) accel = 0.75;
    else if(p->pdv > p->pdvMax/3) accel = 1.0;
    else if(p->pdv <= p->pdvMax/3) accel = 1.25;

    if(p->droite == 1)
    {
        p->hb.x+= p->spd*accel;
        if(p->tex != p->tex_droite)
            p->tex = p->tex_droite;
    }
    if(p->gauche == 1)
    {
        p->hb.x-= p->spd*accel;
        if(p->tex != p->tex_gauche)
            p->tex = p->tex_gauche;
    }

    if(p->hb.y >= 600-p->hb.h*1.10)
            p->hb.y-=2 ;
        if(p->hb.y <= 50)
            p->hb.y+=2;

    if(collision(m,p)== 0)
    {
        p->hb.x = prevX;
        p->hb.y = prevY;

        if(p->droite)
        {
            p->droite = 0;
            p->gauche++;
        }
        else
        {
            p->gauche = 0;
            p->droite++;
        }


    }
}

void eTposeMoves(perso *p, int pX, int pY, map *m, SDL_Window** win, SDL_Renderer **ren){
    if(p->shot[0][0].shot == 0)
        creerTir(p->shot[0], p, pX, pY, win, ren);
    else
    {
        if(p->shot[0][0].hb.x >= SCREEN_WIDTH || p->shot[0][0].hb.x <= 0 || p->shot[0][0].hb.y >= SCREEN_HEIGHT || p->shot[0][0].hb.y <= 0)
            destroyShot(p->shot[0]);
    }
}


// Gere les mouvements du personnage
// Gere le changement de sprite
void persoMove(perso* p, map* m){

    int prevX = p->hb.x;
    int prevY = p->hb.y;

    if(p->droite == 0 && p->gauche == 0 && p->haut == 0 && p->bas == 0)
        p->tex = p->tex_immo;
    else
    {
        /* mouvements en diagonale */
        if(p->droite == 1 && p->haut == 1)
        {
            if(p->tex != p->tex_droite)
                p->tex = p->tex_droite;
            p->hb.x+= p->spd*cos(45);
            p->hb.y-= p->spd*sin(45);
        }
        else if (p->droite == 1 && p->bas == 1)
        {
            if(p->tex != p->tex_droite)
                p->tex = p->tex_droite;
            p->hb.x+= p->spd*cos(45);
            p->hb.y+= p->spd*sin(45);
        }
        else if (p->gauche == 1 && p->haut == 1)
        {
            if(p->tex != p->tex_gauche)
                p->tex = p->tex_gauche;
            p->hb.x-= p->spd*cos(45);
            p->hb.y-= p->spd*sin(45);
        }
        else if (p->gauche == 1 && p->bas == 1)
        {
            if(p->tex != p->tex_gauche)
                p->tex = p->tex_gauche;
            p->hb.x-= p->spd*cos(45);
            p->hb.y+= p->spd*sin(45);
        }

        /* mouvements dans une seule direction */
        else{
            if(p->droite == 1)
            {
                p->hb.x+=p->spd;
                if(p->tex != p->tex_droite)
                    p->tex = p->tex_droite;
            }
            else if(p->gauche == 1)
            {
                p->hb.x-=p->spd;
                if(p->tex != p->tex_gauche)
                    p->tex = p->tex_gauche;
            }
            if(p->bas == 1)
            {
                p->hb.y+=p->spd;
                if(p->tex != p->tex_bas)
                    p->tex = p->tex_bas;
            }
            else if(p->haut == 1)
            {
                p->hb.y-=p->spd;
                if(p->tex != p->tex_haut)
                    p->tex = p->tex_haut;
            }
        }
        /* test des collisions avec le decors */
        if(collision(m,p)== 0)
        {
           p->hb.x = prevX;
           p->hb.y = prevY;
        }
    }
}

// Gere la collision d'un personnage avec le decors
int collision(map *m, perso *p){
    int pHaut   = p->hb.y;
    int pBas    = p->hb.y+p->hb.h;
    int pGauche = p->hb.x;
    int pDroite = p->hb.x+p->hb.w;

    for(int i = 0; i < 84; i++)
    {
        tile t = m->tiletab[i];
        int tHaut   = t.pos.y;
        int tBas    = t.pos.y+t.pos.h-50;
        int tGauche = t.pos.x+25;
        int tDroite = t.pos.x+t.pos.w-25;

        /* BLOCS DURS */
        if(t.num == '2' || t.num == '1' || t.num == '3' || t.num == '5' || t.num == '6')
        {
           if(tHaut < pBas && tBas > pHaut && tGauche < pDroite && tDroite > pGauche)
                return 0;
        }
        /* TROU */
        if(t.num == '4')
        	if(tHaut+25 < pBas && tBas-45 > pHaut && tGauche+45 < pDroite && tDroite-45 > pGauche)
                return 0;
    }
    return 1;
}

// Detection du passage des portes
void porteCol(perso *p, perso e[3], map *m, int *i,char* path[6], SDL_Window **win, SDL_Renderer **ren){
	/* porte a droite */
	if(p->hb.x > SCREEN_WIDTH)
	{
		(*i)++;
		p->hb.x = 0;
        loadRoom(e, p, *i, win, ren);
		LoadMap(m,path[*i]);
		InitMap(m,*ren,*win);

	}
	/* porte a gauche */
	if(p->hb.x+100 < 0)
	{
		(*i)--;
		p->hb.x = SCREEN_WIDTH;
        loadRoom(e, p, *i, win, ren);
		LoadMap(m,path[*i]);
		InitMap(m,*ren,*win);
    }
}

// Gere les collision personnage<->ennemi
void charCol(perso *p, perso e[3], SDL_Window **win, SDL_Renderer **ren){
    int pHaut   = p->hb.y;
    int pBas    = p->hb.y+p->hb.h;
    int pGauche = p->hb.x;
    int pDroite = p->hb.x+p->hb.w;

    for(int i=0; i<3; ++i)
    {
        int eHaut   = e[i].hb.y+45;
        int eBas    = e[i].hb.y+e[i].hb.h-45;
        int eGauche = e[i].hb.x;
        int eDroite = e[i].hb.x+e[i].hb.w;

        if(pHaut < eBas && pBas > eHaut && pGauche < eDroite && pDroite > eGauche)
            pDmg(p, e[i].atk, win, ren);
    }
}

// Gere la collision des tirs
void tirCol(tir *t, perso *p, perso *e, font *f, SDL_Window **win, SDL_Renderer **ren){

    int eHaut   = e->hb.y+10;
    int eBas    = e->hb.y+e->hb.h-10;
    int eGauche = e->hb.x+10;
    int eDroite = e->hb.x+e->hb.w-10;

    for(int j=0; j<(p->nTir); ++j)
    {
        int tHaut   = t[j].hb.y;
        int tBas    = t[j].hb.y+t[j].hb.h;
        int tGauche = t[j].hb.x;
        int tDroite = t[j].hb.x+t[j].hb.w;

        if(tHaut < eBas && tBas > eHaut && tGauche < eDroite && tDroite > eGauche)
        {
            destroyShot(t+j);
            pDmg(e, p->atk, win,ren);

            if(e->pdv<=0)
            {
                destroyPerso(e);
                updateMoney(f, &p->money, 100, win, ren);
            }
            else tirKnockback(t[j].knockback, t[j].dx, t[j].dy, &eGauche, &eDroite, &eHaut, &eBas, &e->hb);
        }
    }
}

// Recul quand blesse par un tir
void tirKnockback(int kb, int dx, int dy, int *eGauche, int *eDroite, int *eHaut, int* eBas, SDL_Rect *eHB){
    if(dx > 0)
        eHB->x += kb;
    else
        eHB->x -= kb;
    if(dy > 0)
        eHB->y += kb;
    else
        eHB->y -= kb;

    if(*eGauche < 100)
        eHB->x += kb;
    else if(*eDroite > 1100)
        eHB->x -= kb;
    if(*eHaut < 100)
        eHB->y += kb;
    else if(*eBas >600)
        eHB->y -= kb;
}

// Gere le changement de salle
void loadRoom(perso e[3], perso* p, int map_i, SDL_Window **win, SDL_Renderer **ren){
    for(int i=0; i<3; ++i)
        destroyPerso(&e[i]);

    switch(map_i)
    {
        //////////////////////////
        /*    SALLE NUMERO 1   */
        /////////////////////////
        case 1:
            chgEnnemi(&e[0], 0, 100*-2, 100*-2, 0,0, 0 ,win, ren);
            chgEnnemi(&e[1], 0, 100*10, 100*2, 5,30, 10 ,win, ren);
            chgEnnemi(&e[2], 0, 100*10, 100*4, 5,30, 10 ,win, ren);
            break;

        //////////////////////////
        /*    SALLE NUMERO 2   */
        /////////////////////////
        case 2:
            chgEnnemi(&e[0], 1, 100*1, 100*5, 0, 30,5 ,win, ren);
            chgEnnemi(&e[1], 1, 100*10, 100*5, 0, 30,5 ,win, ren);
            chgEnnemi(&e[2], 1, 100*1, 100*1, 0, 30,5 ,win, ren);
            break;


        //////////////////////////
        /*    SALLE NUMERO 3   */
        /////////////////////////
        case 3:
            chgEnnemi(&e[0], 0, 100*10, 100*2, 5, 40, 5, win, ren);
            chgEnnemi(&e[1], 0, 100*1, 100*1, 5, 40, 5 , win, ren);
            chgEnnemi(&e[2], 0, 100*5, 100*5, 5, 40, 5, win, ren);
            break;

        //////////////////////////
        /*    SALLE NUMERO 4   */
        /////////////////////////
        case 4:
            // magasin
            break;

        //////////////////////////
        /*    SALLE NUMERO 5   */
        /////////////////////////
        case 5:
            p->hb.x = 200;
            chgEnnemi(&e[0], 0, 100*5, 250, 15, 100, 7, win, ren);
            e[0].hb.w = 200; e[0].hb.h = 200;
            chgEnnemi(&e[1], 0, -150, -150, 15, 100, 7, win, ren);
            chgEnnemi(&e[2], 0, -150*5, -150, 15, 100, 7, win, ren);
            break;

        default:
            break;
    }
}

// Gere l'actualisation des ennemis en fonction de la salle acutelle
void updateRoom(perso e[3], perso *p, map *m, int map_i, SDL_Rect *R, font *f, uint32_t tick, SDL_Window **win, SDL_Renderer **ren){

    switch(map_i)
    {
        //////////////////////////
        /*    SALLE NUMERO 1   */
        /////////////////////////
        case 1:
            for(int j=0; j<3; ++j)
            {
                if(e[j].pdv > 0)
                {
                    eBlindMoves(&e[j], m, win, ren);
                    SDL_RenderCopy(*ren, e[j].tex, R, &e[j].hb);
                    updatePerso(&e[j], *R, tick, win, ren);
                }
            }
            break;

        //////////////////////////
        /*    SALLE NUMERO 2   */
        /////////////////////////
        case 2:
            for(int j=0; j<3; ++j)
            {
                if(e[j].pdv > 0)
                {
                    eTposeMoves(&e[j], p->hb.x+10, p->hb.y+40, m, win, ren);
                    SDL_RenderCopy(*ren, e[j].tex, R, &e[j].hb);
                    updatePerso(&e[j], *R, tick, win, ren);
                    if(e[j].shot[0][0].shot)
                    {
                        tirer(e[j].shot[0], win, ren);
                        tirCol(e[j].shot[0], &e[j], p, f, win, ren);
                        SDL_RenderCopy(*ren, e[j].shot[0][0].tex, NULL, &e[j].shot[0][0].hb);
                    }
                }
            }
            break;


        //////////////////////////
        /*    SALLE NUMERO 3   */
        /////////////////////////
        case 3:
            for(int j=0; j<3; ++j)
            {
                if(e[j].pdv > 0)
                {
                    eBlindMoves(&e[j], m, win, ren);
                    SDL_RenderCopy(*ren, e[j].tex, R, &e[j].hb);
                    updatePerso(&e[j], *R, tick, win, ren);
                }
            }
            break;

        //////////////////////////
        /*    SALLE NUMERO 5   */
        /////////////////////////
        case 5:
            eBlindMoves(&e[0], m, win, ren);
            SDL_RenderCopy(*ren, e[0].tex, R, &e[0].hb);
            updatePerso(&e[0], *R, tick, win, ren);
            if(e[0].pdv <= 0)
                p->money+=1000;
            break;

        default:
            break;
    }
}

// Gere la prise de degat
// Donne un temps avant de reprendre une seconde fois des degats
void pDmg(perso *p, int dmg, SDL_Window **win, SDL_Renderer **ren){
    uint32_t currTick = SDL_GetTicks();

    if(currTick - p->prevDmgTick >= p->invFrm)
    {
        char arr[3];
        sprintf(arr, "%d",dmg);
        p->pdv-= dmg;
        p->prevDmgTick = currTick;
        setTTF(p->popup, 24, ROUGE, arr, p->hb.x, p->hb.y, 500, win, ren);
    }
}

// Gere la destruction des ennemis
void destroyPerso(perso *p){

    p->spd = 0;
    p->hb.x = -150; p->hb.y = -150;
    if(p->shot[0]->shot == 1)
        destroyShot(p->shot[0]);

}

// Cree la barre de vie
void createHealthbar(healthbar *health, SDL_Window **win, SDL_Renderer **ren){
    loadIMG("./images/SPRITE_PROJET_VIE_BARRE.png",&health->surf,&health->tBarre,win,ren);
    if(SDL_QueryTexture(health->tBarre, NULL, NULL, &health->rBarre.w, &health->rBarre.h) != 0)
        QuitErrorWR("Creation de la hitbox de la barre de vie non creee", win ,ren);
    health->rBarre.x = 52;
    health->rBarre.y = 0;

    loadIMG("./images/SPRITE_PROJET_VIE_HUD.png",&health->surf,&health->tHud,win,ren);
    if(SDL_QueryTexture(health->tHud, NULL, NULL, &health->rHud.w, &health->rHud.h) != 0)
        QuitErrorWR("Creation de l'hud de la vie non cree", win ,ren);
    health->rHud.x = 0;
    health->rHud.y = 0;

    health->rBarreMod.x = health->rHud.x;
    health->rBarreMod.y = health->rHud.y;
    health->rBarreMod.w = health->rHud.w;
    health->rBarreMod.h = health->rHud.h;

    health->len = 136;
}

// Met a jour la barre de vie
void updateHealthbar(healthbar *health, int pdv, int pdvMax){
    health->pourcent = ((float)pdv/pdvMax);
    health->rBarre.w = health->len * health->pourcent;
    health->rBarreMod.w = health->len * health->pourcent;
}

// afiche le perso ainsi que le popup de vie
void updatePerso(perso *p, SDL_Rect r, uint32_t tick, SDL_Window **win, SDL_Renderer **ren){
    SDL_RenderCopy(*ren, p->tex, &r, &p->hb);
    if(tick-FPS_LIMIT <= p->popup->poped+p->popup->duree)
    {
        p->popup->rect.x = p->hb.x+p->hb.w/2;
        p->popup->rect.y = p->hb.y-p->popup->rect.h;
        SDL_RenderCopy(*ren, p->popup->tex, NULL, &p->popup->rect);
    }
}


