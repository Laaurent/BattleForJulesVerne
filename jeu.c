#include "jeu.h"

//limite les fps du jeu
void fpsLimit(unsigned int lim){
    unsigned int ticks = SDL_GetTicks();
    if(lim < ticks) return;
    else if(lim > ticks + FPS_LIMIT) SDL_Delay(FPS_LIMIT);
    else SDL_Delay(lim - ticks);
}

void jouer(int** loop,SDL_Renderer** ren,SDL_Window** win){

    // VAR BOUCLE
    int game = 1;
    SDL_Event event;
    int souris_x, souris_y;
    Uint32 sprite = 0;
    unsigned int fpslim;
    // VAR BOUCLE


    //VAR MAGASIN
    SDL_Surface *surf_shop;
    SDL_Texture *tex_shop_heal;
    SDL_Texture *tex_shop_tirUp;
    SDL_Texture *tex_shop_tirUp2;
    loadIMG("./images/SPRITES_20_HP.png", &surf_shop, &tex_shop_heal, win, ren);
    loadIMG("./images/SPRITES_TIRS_UP.png", &surf_shop, &tex_shop_tirUp, win, ren);
    loadIMG("./images/SPRITES_TIRS_UP_2.png", &surf_shop, &tex_shop_tirUp2, win, ren);

    SDL_Rect RectHeal={250,200,200,50};
    SDL_Rect RectTirUp={500,200,200,50};
    SDL_Rect RectTirUp2={750,200,200,50};
    //VAR MAGASIN


    /////////////////////
    /* Perso principal */
    /////////////////////
    perso *p = (perso*)malloc(sizeof(perso));
    creerPerso(p, win, ren);

    SDL_Surface *tmp;
    tir** shot = p->shot;
    *shot = (tir*)malloc((p->nTir)*sizeof(tir));
    for(int i=0; i<(p->nTir); ++i)
    {
        ((*shot)[i]).shot = 0;
        loadIMG("./images/BALLE_CIRCLE.png", &tmp, &p->shot[i]->tex, win, ren);
    }
    // barre de vie du perso
    healthbar *health = (healthbar*)malloc(sizeof(healthbar));
    createHealthbar(health, win, ren);

    //indicateur d'argent du perso
    moneyHud *mHud = (moneyHud*)malloc(sizeof(moneyHud));
    createMoney(mHud, win, ren);
    font *argentPolice =(font*)malloc(sizeof(font));
    setTTF(argentPolice, 42, VERT, "0", 310, 0, -1, win, ren);


    /* Ennemis */
    perso e[3];
    for(int i=0; i<3; ++i)
        creerEnnemi(&e[i], win, ren);

    // map
    map Map;
    int Map_i = 0;
    char* mapPath[6] = {"./map/map1_1.map", "./map/map1_2.map", "./map/map1_3.map", "./map/map1_4.map", "./map/map1_5.map", "./map/map1_6.map" };
    LoadMap(&Map,mapPath[Map_i]);
    InitMap(&Map,*ren,*win);
    loadRoom(e, p, Map_i, win, ren);

    // Image de fond
    menu menu_fond;
    initImageMenu(&menu_fond, "./images/menu.png", ren, win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,0);

    /* MUSIQUE */
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
        QuitErrorWR((char*)Mix_GetError(), win, ren);
    Mix_Music *bgm = Mix_LoadMUS("./sounds/Main_Theme.wav");

    while(game)
    {
        fpslim = SDL_GetTicks() + FPS_LIMIT;

        if (**loop==0)
            game = 0;

        /* ECRAN DE VICTOIRE */
        // W  I  P
        if(p->money >= 1000)
            menuPause(ren,win,loop, &game, (int)WIN);

        /* ECRAN DE DEFAITE */
        if(p->pdv <= 0)
            menuPause(ren,win,loop, &game, (int)LOSE);

        if(!Mix_PlayingMusic())
            Mix_PlayMusic(bgm, 1);

        // ANIMATION DES SPRITES : variables
        sprite = SDL_GetTicks() /100 %6;
        SDL_Rect srcrect = { sprite * 100, 0, 100, 600 };

        SDL_GetMouseState(&souris_x,&souris_y);

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_d:
                        case SDLK_RIGHT:
                            p->droite=1;
                            break;
                        case SDLK_q:
                        case SDLK_LEFT:
                            p->gauche=1;
                            break;
                        case SDLK_z:
                        case SDLK_UP:
                            p->haut=1;
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            p->bas=1;
                            break;
                            /* MUSIQUE */
                            break;
                        case SDLK_p:
                            if(!Mix_PlayingMusic())
                                Mix_PlayMusic(bgm, 1);
                            else if(Mix_PausedMusic())
                                Mix_ResumeMusic();
                            else
                                Mix_PauseMusic();
                            break;
                        default:
                            break;
                    }break;
                }
                case SDL_KEYUP:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_d:
                        case SDLK_RIGHT:
                            p->droite=0;
                            break;
                        case SDLK_q:
                        case SDLK_LEFT:
                            p->gauche=0;
                            break;
                        case SDLK_z:
                        case SDLK_UP:
                            p->haut=0;
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            p->bas=0;
                            break;
                        case SDLK_ESCAPE:
                            menuPause(ren,win,loop, &game, (int)PAUSE);
                            break;

                        // MAGASIN
                        case SDLK_e:
                            if(Map_i == 4)
                            {
                                // PREMIER OBJET MAGASIN
                                if(p->money >= 100 && p->pdv < p->pdvMax &&
                                   p->hb.x >= 250 && p->hb.x <= 450 &&
                                   p->hb.y >= 100 && p->hb.y <= 300)
                                {
                                    updateMoney(argentPolice, &p->money, -100, win, ren);
                                    if(p->pdv >= p->pdvMax-20)
                                        p->pdv = p->pdvMax;
                                    else
                                        p->pdv+=20;
                                    printf("Soin PV +20\n");
                                }

                                // DEUXIEME OBJET MAGASIN
                                if(p->money >= 200 && p->hb.x >= 500 && p->hb.x <= 700 &&
                                   p->hb.y >= 100 && p->hb.y <= 300)
                                {
                                    updateMoney(argentPolice, &p->money, -200, win, ren);
                                    p->nTir = 3;
                                    p->cdTir = 200;
                                    *shot = (tir*)realloc(*shot,(p->nTir)*sizeof(tir));
                                    p = (perso*)realloc(p,sizeof(*shot)+sizeof(perso));
                                    printf("Tir ameliores: %d\n", p->cdTir);
                                }

                                // TROISIEME OBJET MAGASIN
                                if(p->hb.x >= 750 && p->hb.x <= 950 &&
                                   p->hb.y >= 100 && p->hb.y <= 300)
                                {
                                    p->nTir = 5;
                                    p->cdTir = 50;
                                    p->pdvMax = 50;
                                    if(p->pdv > 50)
                                        p->pdv =50;
                                    *shot = (tir*)realloc(*shot,(p->nTir)*sizeof(tir));
                                    p = (perso*)realloc(p,sizeof(*shot)+sizeof(perso));
                                    printf("Tir ameliores+: %d\n", p->cdTir);
                                }
                            }
                            break;
                        // MAGASIN*/
                    }break;
                }

                // Tir si aucun autre tir
                case SDL_MOUSEBUTTONDOWN:
                    for(int i=0; i<(p->nTir); ++i)
                        if(shot[0][i].shot == 0)
                            creerTir(&shot[0][i], p, souris_x, souris_y, win, ren);
                    break;
                // Quitter le jeu
                case SDL_QUIT:
                    game = 0;
                    **loop = 0;
                    break;
                default:
                    break;
            }
        }
        // detruit le tir si il est hors de la zone de tir
        // ou alors qu'il atteint sa distance max
        for(int i=0; i<(p->nTir); ++i)
        {
            if(shot[0][i].shot == 1)
            {
                tirer(&shot[0][i], win, ren);
                if(shot[0][i].hb.x >= SCREEN_WIDTH || shot[0][i].hb.x <= 0 || shot[0][i].hb.y >= SCREEN_HEIGHT || shot[0][i].hb.y <= 0 ||
                   shot[0][i].dst <= SDL_GetTicks())
                    destroyShot(&shot[0][i]);
            }
        }

        // mouvements du perso
        persoMove(p, &Map);


        // collisions
        porteCol(p, e, &Map, &Map_i, mapPath, win, ren);
        for(int i=0; i<3; ++i)
            tirCol(shot[0], p, &e[i], argentPolice, win, ren);
        charCol(p, e, win, ren);


        //////////////////////////
        // * RENDU DES IMAGES * //
        //////////////////////////


        SDL_RenderClear(*ren);

        SDL_RenderCopy(*ren, menu_fond.tex, NULL, &menu_fond.pos);
        DrawMap(&Map,*ren);

        // ENNEMIS : paternes, sprites
        updateRoom(e, p, &Map, Map_i, &srcrect, argentPolice, fpslim, win, ren);

        // BARRE DE VIE
        updateHealthbar(health, p->pdv, p->pdvMax);
        SDL_RenderCopy(*ren,health->tBarre, &health->rBarreMod, &health->rBarre);
        SDL_RenderCopy(*ren,health->tHud, NULL, &health->rHud);

        // Argent HUD
        SDL_RenderCopy(*ren, mHud->tex, NULL, &mHud->rect);
        SDL_RenderCopy(*ren, argentPolice->tex, NULL, &argentPolice->rect);


        // MAGASIN (room 4)
        if(Map_i == 4)
        {
            SDL_RenderCopy(*ren, tex_shop_heal, NULL, &RectHeal);
            SDL_RenderCopy(*ren, tex_shop_tirUp, NULL, &RectTirUp);
            SDL_RenderCopy(*ren, tex_shop_tirUp2, NULL, &RectTirUp2);
        }



        // PERSO : sprite + popup
        updatePerso(p, srcrect, fpslim, win, ren);

        // TIRS
        for(int i=0; i<(p->nTir); ++i)
        {
            if((*(*shot+i)).shot == 1)
                SDL_RenderCopy(*ren, (*(*shot+i)).tex, NULL, &(*(*shot+i)).hb);
        }
        // afichage de toutes les images
        SDL_RenderPresent(*ren);

        // Limite les images par seconde a 60
        fpsLimit(fpslim);
    }

    Mix_CloseAudio();
    free(tex_shop_heal);
    free(tex_shop_tirUp2);
    free(tex_shop_tirUp);
    free(argentPolice);
    free(bgm);
    free(p->shot);
    free(p->shot[0]);
    free(shot);
    free(health);
    free(p);
}
