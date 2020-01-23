#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "menu.h"
#include "gui.h"
#include "jeux.h"

// initialise SDL et tous les autres biblio associe
void initializerSDL(SDL_Window** win,SDL_Renderer** rend,TTF_Font** font)
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    *win = SDL_CreateWindow("Motus",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR, HAUTEUR, 0);
    *rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    *font = TTF_OpenFont("ressources/police.ttf",200);
}

// ferme SDL et libere la memoire
void fermerSDL(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

// initialise une variable de type etatJeux
void initializerEtatJeux(etatJeux* monEtat,options* mesOptions)
{
    monEtat->taille = 6;
    //mesOptions->tailleMot
    monEtat->tempsReflexion = TEMPSREF;
    //mesOptions->tempsReflexion*60
    monEtat->tentative = 1;
    monEtat->curseur = 0;
    monEtat->score = 0;
    genererMot(monEtat->mot,monEtat->taille);
    monEtat->etatPartie = ENCOURS;
    for(int i=0;i<7;i++)
    {
        initializerMot(&monEtat->evaluation[i][0],'F',monEtat->taille);
        initializerMot(&monEtat->input[i][0],NULL,11);
    }
    initializerMot(monEtat->decouvert,0,11);
    srand(time(NULL));
    int r = rand()%(monEtat->taille-1);
    monEtat->decouvert[0] = 1;
    monEtat->decouvert[1+r] = 1;
}

// initialise le tableau de rectangles qui constitue la grille de jeux selon la taille des mots
void grille(SDL_Rect rectangles[],int taille)
{
    // les element de la grille
    for(int i=0;i<taille*7;i++)
    {
        rectangles[i].h = TAILLEGRILLE;
        rectangles[i].w = TAILLEGRILLE;
        rectangles[i].x = POSGRILLEX+(i%taille)*(TAILLEGRILLE+DISTGRILLE);
        rectangles[i].y = POSGRILLEY+(i/taille)*(TAILLEGRILLE+DISTGRILLE);
    }
    // le curseur (juste les dimensions , la position est variable)
    rectangles[taille*7].h = TAILLEGRILLE/10;
    rectangles[taille*7].w = TAILLEGRILLE;
    // le rectangle tentative (juste les dimensions et la position x, la position y est variable)
    rectangles[taille*7+1].h = TAILLEGRILLE + 2*DISTGRILLE;
    rectangles[taille*7+1].w = TAILLEGRILLE*taille +(taille+1)*DISTGRILLE;
    rectangles[taille*7+1].x = POSGRILLEX - DISTGRILLE;
}

// affiche et render tous les objets
void afficher(SDL_Rect rectangles[],SDL_Renderer* rend,etatJeux* monEtat,SDL_Texture* lettres[],SDL_Texture* rondJaune,TTF_Font *font)
{
    // affichage de la grille
    SDL_SetRenderDrawColor(rend,53,59,72,255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend,41,128,185,255);
    SDL_RenderFillRects(rend,rectangles,(monEtat->taille)*7);
    // affiche de l'evaluation (carre rouge ou rond jaune)
    SDL_SetRenderDrawColor(rend,255,0,0,255);
    int iter = (monEtat->tentative-1)*monEtat->taille;
    for(int i=0;i<iter;i++)
    {
        if(monEtat->evaluation[i/monEtat->taille][i%monEtat->taille] == 'V')
            SDL_RenderFillRect(rend,&rectangles[i]);
        else if(monEtat->evaluation[i/monEtat->taille][i%monEtat->taille] == 'P')
            SDL_RenderCopy(rend, rondJaune, NULL, &rectangles[i]);
    }
    // affichage des lettres
    iter = (monEtat->tentative)*monEtat->taille;
    for(int i=0;i<iter;i++)
    {
        if(monEtat->input[i/monEtat->taille][i%monEtat->taille] != NULL )
            SDL_RenderCopy(rend, lettres[monEtat->input[i/monEtat->taille][i%monEtat->taille]-97], NULL, &rectangles[i]);

    }
    // affichage du curseur
    rectangles[(monEtat->taille)*7].x = rectangles[(monEtat->tentative-1)*monEtat->taille+monEtat->curseur].x;
    rectangles[(monEtat->taille)*7].y = rectangles[(monEtat->tentative-1)*monEtat->taille+monEtat->curseur].y + TAILLEGRILLE - TAILLEGRILLE/10;
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    SDL_RenderFillRect(rend,&rectangles[(monEtat->taille)*7]);
    // affichage du rectangle tentative
    rectangles[(monEtat->taille)*7+1].y = rectangles[(monEtat->tentative-1)*monEtat->taille].y - DISTGRILLE;
    SDL_SetRenderDrawColor(rend,52,73,94,100);
    SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_ADD);
    SDL_RenderFillRect(rend,&rectangles[(monEtat->taille)*7+1]);
    SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_NONE);
    // affichage du temps restant
    static SDL_Color white = {255,255,255};
    char temps[10];
    sprintf(temps, "%d",(int)monEtat->tempsReflexion/60);
    SDL_Surface* surface = TTF_RenderText_Blended(font,temps,white);
    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_Rect cadre;
    SDL_QueryTexture(text,NULL,NULL,&cadre.w,&cadre.h);
    cadre.h /= 7;
    cadre.w /= 7;
    cadre.x = TEMPSX;
    cadre.y = TEMPSY;
    SDL_RenderCopy(rend,text,NULL,&cadre);
    SDL_DestroyTexture(text);
    SDL_RenderPresent(rend);
}

// charge les textures des lettre et du rond jaune
void initializerTextures(SDL_Renderer* rend,SDL_Texture** rondJaune,SDL_Texture* lettres[],TTF_Font *font)
{
    // chargement de la texture du rond jaune
    static SDL_Color white = {255,255,255};
    static SDL_Texture* text;
    SDL_Surface* surface = IMG_Load("ressources/cercle.png");
    *(rondJaune) = SDL_CreateTextureFromSurface(rend,surface);
    // chargement des textures des lettres
    char let[2];
    let[1] = '\0';
    for(int i=0;i<26;i++)
    {
        let[0] = 65+i;
        surface = TTF_RenderText_Solid(font,let,white);
        text = SDL_CreateTextureFromSurface(rend, surface);
        lettres[i] = text;
    }
    SDL_FreeSurface(surface);
}

// change l'etat de la partie en cas de perte ou victoire
void changerEtat(etatJeux* monEtat,options* mesOptions)
{
    static int initializerVrai = 0;
    static char vrai[11];
    if(!initializerVrai)
    {
        initializerVrai = 1;
        initializerMot(vrai,'V',monEtat->taille);
    }
    if(monEtat->tentative>7)
    {
        if(strcmp(monEtat->evaluation[monEtat->tentative-2],vrai))
        {
            monEtat->etatPartie = PERDU;
        }
        else
        {
            int temp = monEtat->score+1;
            initializerEtatJeux(monEtat,mesOptions);
            monEtat->score = temp;
            afficherAide(monEtat);
        }
    }
    else if(!strcmp(monEtat->evaluation[monEtat->tentative-2],vrai))
    {
        int temp = monEtat->score+1;
        initializerEtatJeux(monEtat,mesOptions);
        monEtat->score = temp;
        afficherAide(monEtat);
    }
}

// convertie un caractere utf8 en ascci en enlevant tous les cracteres non desire
char utf8EnAscii(char utf8[])
{
    char lettre = utf8[0];
    // garder que les lettres de a-z
    if(lettre >= 65 && lettre <= 90)
        lettre += 32;
    if(lettre <97 || lettre >122)
        lettre = 48;
    return lettre;
}

// mise a jour de l'etat du jeux
void miseAjour(char lettre,etatJeux* monEtat,char dictionnaire[])
{
    // cas entrer
    if(lettre == 0)
    {
        if(motValable(&(monEtat->input[monEtat->tentative-1][0]),monEtat->taille,monEtat->mot[0],dictionnaire))
            comparer(&(monEtat->input[monEtat->tentative-1][0]),monEtat->mot,&(monEtat->evaluation[monEtat->tentative-1][0]),monEtat->taille);
        monEtat->tentative++;
        monEtat->curseur = 0;
        monEtat->tempsReflexion = TEMPSREF;
        afficherAide(monEtat);
    }
    // cas del
    else if(lettre == 1)
    {
        monEtat->input[monEtat->tentative-1][monEtat->curseur-1] = NULL;
        monEtat->curseur--;
    }
    // cas text
    else if(lettre != 48)
    {
        monEtat->input[monEtat->tentative-1][monEtat->curseur] = lettre;
        if(monEtat->curseur<monEtat->taille-1)
            monEtat->curseur++;
    }
    // dimunition du temps de reflexion et passage a la tentative suivant en cas de sa consommation
    monEtat->tempsReflexion--;
    if(monEtat->tempsReflexion<0)
    {
        monEtat->tentative++;
        monEtat->curseur = 0;
        monEtat->tempsReflexion = TEMPSREF;
    }
}

// affiche a chaque tentative un aide(la premiere fois la premiere lettre et une autre au hazard, et par la suite les lettres decouvertes)
void afficherAide(etatJeux* monEtat)
{
    static int premiereFois = 1;
    if(!premiereFois)
    {
        for(int i=0;i<monEtat->taille;i++)
        {
            if(monEtat->evaluation[monEtat->tentative-2][i]=='V')
                monEtat->decouvert[i] = 1;
        }
    }
    if(premiereFois)
        premiereFois = 0;
    for(int i=0;i<monEtat->taille;i++)
    {
        if(monEtat->decouvert[i]==1)
            monEtat->input[monEtat->tentative-1][i] = monEtat->mot[i];
    }

}
