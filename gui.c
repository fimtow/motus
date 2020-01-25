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
    monEtat->taille = mesOptions->tailleMot;
    monEtat->tempsReflexion = mesOptions->tempsReflexion*60;
    monEtat->tentative = 1;
    monEtat->curseur = 0;
    monEtat->score = 0;
    genererMot(monEtat->mot,monEtat->taille,mesOptions->difficulte+1);
    monEtat->etatPartie = ENCOURS;
    for(int i=0;i<7;i++)
    {
        initializerMot(&monEtat->evaluation[i][0],'F',monEtat->taille);
        initializerMot(&monEtat->input[i][0],NULL,monEtat->taille);
    }
    initializerMot(monEtat->decouvert,0,monEtat->taille);
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
    char temps[10];
    static SDL_Color blanc = {255,255,255};
    sprintf(temps, "%d",(int)monEtat->tempsReflexion/60);
    afficherText(temps,250,410,3);
    // affichage du score
    char score[10];
    sprintf(score, "%d",(int)monEtat->score);
    afficherText(score,570,410,3);
    // affichage des texts
    afficherText("TEMPS :",10,410,3);
    afficherText("SCORE :",340,410,3);
    SDL_RenderPresent(rend);
}

// charge les textures des lettre et du rond jaune
void initializerTextures(SDL_Renderer* rend,SDL_Texture** rondJaune,SDL_Texture* lettres[],TTF_Font *font)
{
    // chargement de la texture du rond jaune
    static SDL_Texture* text;
    SDL_Surface* surface = IMG_Load("ressources/cercle.png");
    *(rondJaune) = SDL_CreateTextureFromSurface(rend,surface);
    // chargement des textures des lettres
    char let[2];
    static SDL_Color blanc = {255,255,255};
    let[1] = '\0';
    for(int i=0;i<26;i++)
    {
        let[0] = 65+i;
        surface = TTF_RenderText_Solid(font,let,blanc);
        text = SDL_CreateTextureFromSurface(rend, surface);
        lettres[i] = text;
    }
    SDL_FreeSurface(surface);
}

// change l'etat de la partie en cas de perte ou victoire
void changerEtat(etatJeux* monEtat,options* mesOptions,char*** dictionnaire,int *nbr)
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
            printf("%s",monEtat->mot);
            // initialisation du dictionnaire
            free(*dictionnaire);
            *dictionnaire = initializerDictionnaire(*dictionnaire,monEtat->mot[0],nbr);
        }
    }
    else if(!strcmp(monEtat->evaluation[monEtat->tentative-2],vrai))
    {
        int temp = monEtat->score+1;
        initializerEtatJeux(monEtat,mesOptions);
        monEtat->score = temp;
        afficherAide(monEtat);
        printf("%s",monEtat->mot);
        // initialisation du dictionnaire
        free(*dictionnaire);
        *dictionnaire = initializerDictionnaire(*dictionnaire,monEtat->mot[0],nbr);
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
void miseAjour(char lettre,etatJeux* monEtat,char** dictionnaire,int tailleDictio)
{
    // cas entrer
    if(lettre == 0)
    {
        if(motValable(&(monEtat->input[monEtat->tentative-1][0]),monEtat->taille,monEtat->mot[0],dictionnaire,tailleDictio))
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
        afficherAide(monEtat);
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

//fonction qui affiche du text
void afficherText(char text[],int x,int y,int taille)
{
    static SDL_Color blanc = {255,255,255};
    SDL_Surface* surface = TTF_RenderText_Blended(font,text,blanc);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend,surface);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h);
    rectangle.w /= 10;
    rectangle.h /= 10;
    rectangle.w *= taille;
    rectangle.h *= taille;
    SDL_RenderCopy(rend,texture,NULL,&rectangle);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void afficherParametres(char options[],int nbop,int longueur,int* etat,int x,int y,int w,int h,int clique)
{
    SDL_Surface* surface = IMG_Load("ressources/fleche.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend,surface);
    SDL_Rect rectangle;
    rectangle.w = w;
    rectangle.h = h;
    SDL_Rect fleche;
    fleche.w = fleche.h = h;
    fleche.x = x;
    fleche.y = y;
    rectangle.y = y;
    rectangle.x = x+h+10;
    SDL_RenderCopyEx(rend,texture,NULL,&fleche,180,NULL,SDL_FLIP_VERTICAL);
    SDL_SetRenderDrawColor(rend,41,128,185,255);
    SDL_RenderFillRect(rend,&rectangle);
    fleche.x = rectangle.x + w + 10;
    SDL_RenderCopy(rend,texture,NULL,&fleche);
    if(clique)
    {
        int posx;
        int posy;
        SDL_GetMouseState(&posx,&posy);
        if(posx>=x && posx<=x+h && posy>=y && posy<=y+h)
        {
            (*etat)--;
            if(*etat<0)
                *etat = nbop-1;
        }
        else if(posx>=fleche.x && posx<=fleche.x+h && posy>=y && posy<=y+h)
        {
            (*etat)++;
            if(*etat>=nbop)
                *etat = 0;
        }
    }
    afficherText(&options[longueur*(*etat)],rectangle.x+w/8,rectangle.y,2);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
