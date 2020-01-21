#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "gui.h"
#include "jeux.h"

void initializerSDL(SDL_Window** win,SDL_Renderer** rend,TTF_Font** font)
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    *win = SDL_CreateWindow("Motus",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR, HAUTEUR, 0);
    *rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    *font = TTF_OpenFont("ressources/police.ttf",50);
}

void fermerSDL(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

void initializerEtatJeux(etatJeux* monEtat)
{
    monEtat->taille = 6;
    monEtat->tentative = 1;
    monEtat->curseur = 0;
    genererMot(monEtat->mot,monEtat->taille);
    monEtat->etatPartie = ENCOURS;
    for(int i=0;i<7;i++)
        initializerMot(&monEtat->evaluation[i][0],'F',monEtat->taille);
}

void grille(SDL_Rect rectangles[],int taille)
{
    for(int i=0;i<taille*7;i++)
    {
        rectangles[i].h = TAILLEGRILLE;
        rectangles[i].w = TAILLEGRILLE;
        rectangles[i].x = POSGRILLEX+(i%taille)*(TAILLEGRILLE+DISTGRILLE);
        rectangles[i].y = POSGRILLEY+(i/taille)*(TAILLEGRILLE+DISTGRILLE);
    }
}

void afficher(SDL_Rect rectangles[],SDL_Renderer* rend,etatJeux* monEtat,SDL_Texture* lettres[])
{
    SDL_SetRenderDrawColor(rend,53,59,72,255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend,41,128,185,255);
    SDL_RenderFillRects(rend,rectangles,(monEtat->taille)*7);
    for(int i=0;i<monEtat->curseur;i++)
    {
        SDL_RenderCopy(rend, lettres[monEtat->input[0][i]-65], NULL, &rectangles[i]);
    }
    SDL_RenderPresent(rend);
}

void initializerTextures(SDL_Renderer* rend,SDL_Texture** rondJaune,SDL_Texture* lettres[],TTF_Font *font)
{
    static SDL_Color white = {255,255,255};
    static SDL_Texture* text;
    SDL_Surface* surface = IMG_Load("ressources/cercle.png");
    *(rondJaune) = SDL_CreateTextureFromSurface(rend,surface);
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

void changerEtat(etatJeux* monEtat)
{
    static int initializerVrai = 0;
    // table may lost its data
    static char* vrai;
    if(!initializerVrai)
    {
        initializerVrai = 1;
        initializerMot(vrai,'V',monEtat->taille);
    }
    if(monEtat->tentative>7)
    {
        if(strcmp(monEtat->evaluation[monEtat->tentative-1],vrai))
            monEtat->etatPartie = PERDU;
        else
            monEtat->etatPartie = GAGNE;
    }
    else if(!strcmp(monEtat->evaluation[monEtat->tentative-1],vrai))
    {
        monEtat->etatPartie = GAGNE;
    }
}

char utf8EnAscii(char utf8[])
{
    char lettre = utf8[0];
    if(lettre >= 97 && lettre <= 122)
        lettre -= 32;
    if(lettre <65 || lettre >90)
        lettre = 48;
    return lettre;
}
void miseAjour(char lettre,etatJeux* monEtat)
{
    if(lettre != 48)
    {
        monEtat->input[monEtat->tentative-1][monEtat->curseur] = lettre;
        monEtat->curseur++;
    }
}

