#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "jeux.h"
#include "mots.h"
#include "menu.h"
#include "gui.h"

//demare le jeux
void jeux(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font,options* mesOptions,int* stop)
{
    // initialisation de l'etat du jeux
    etatJeux* monEtat = (etatJeux*)malloc(sizeof(etatJeux));
    initializerEtatJeux(monEtat,mesOptions);
    printf("%s",monEtat->mot);
    // initialisation du dictionnaire
    int nbr;
    char **dictionnaire = initializerDictionnaire(dictionnaire,monEtat->mot[0],&nbr);


    // initialisation des textures et rectangles (plus le curseur et le rectangle tentative d'ou le +2)
    SDL_Rect rectangles[monEtat->taille*7+2];
    grille(rectangles,monEtat->taille);
    SDL_Texture* lettres[26];
    SDL_Texture* rondJaune;
    initializerTextures(rend,&rondJaune,lettres,font);

    // les variables qui vont stocker temporairement les lettres
    SDL_StartTextInput();
    char lettreUtf8[32];
    char lettre = 48;
    // game loop
    afficherAide(monEtat);
    while(monEtat->etatPartie == ENCOURS)
    {
        // gestion des evenements
        lettre = 48;
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            // clique sur le boutton fermer de la fenetre
            if (event.type == SDL_QUIT)
            {
                monEtat->etatPartie = PERDU;
                *stop = 1;
                break;
            }
            // clique sur le boutton entrer
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                // cela indique a la fonction mise a jour que l'utilisateur a appuye entrer
                lettre = 0;
            }
            // clique sur le boutton delete
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_DELETE && monEtat->curseur != 0)
            {
                // cela indique a la fonction mise a jour que l'utilisateur a appuye del
                lettre = 1;
            }
            // clique sur n'importe quel autre bouton (text)
            else if(event.type == SDL_TEXTINPUT)
            {
                strcpy(lettreUtf8,event.text.text);
                lettre = utf8EnAscii(lettreUtf8);
            }
        }
        // mise a jour de l'etat du jeux
        miseAjour(lettre,monEtat,dictionnaire,nbr);

        // mise a jour de l'etat de la partie
        changerEtat(monEtat,mesOptions,&dictionnaire,&nbr);
        if(monEtat->etatPartie == PERDU)
            break;
        // affichage et render
        afficher(rectangles,rend,monEtat,lettres,rondJaune,font);

        // ajustement du FPS
        SDL_Delay(1000/60);

    }
    if(!*stop)
        votreScore(monEtat->score,stop);
}

// initialise les rectangles et textures du menu
void initializerMenu(SDL_Rect bouttons[],SDL_Texture* text[],TTF_Font *font,SDL_Renderer* rend)
{
    for(int i=0;i<3;i++)
    {
        bouttons[i].w = BOUTTONL;
        bouttons[i].h = BOUTTONH;
        bouttons[i].x = LARGEUR/2-BOUTTONL/2;
        bouttons[i].y = BOUTTONY+(BOUTTONH+BOUTTOND)*i;
    }
    SDL_Surface* surface = IMG_Load("ressources/logo.png");
    text[3] = SDL_CreateTextureFromSurface(rend,surface);
    SDL_QueryTexture(text[3],NULL,NULL,&bouttons[3].w,&bouttons[3].h);
    bouttons[3].w /= 10;
    bouttons[3].h /= 10;
    bouttons[3].x = LARGEUR/2-bouttons[3].w/2;
    bouttons[3].y = 50;
    SDL_Colour blanc = {255,255,255,255};
    surface = TTF_RenderText_Blended(font,"Jouer",blanc);
    text[0] = SDL_CreateTextureFromSurface(rend,surface);
    surface = TTF_RenderText_Blended(font,"Hight Score",blanc);
    text[1] = SDL_CreateTextureFromSurface(rend,surface);
    surface = TTF_RenderText_Blended(font,"Options",blanc);
    text[2] = SDL_CreateTextureFromSurface(rend,surface);
}

// affiche le menu
void afficherMenu(SDL_Window* win,SDL_Renderer* rend,SDL_Rect bouttons[],SDL_Texture* text[])
{
    SDL_SetRenderDrawColor(rend,231,76,60,255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend,241,196,15,255);
    SDL_RenderFillRects(rend,bouttons,3);
    int b = bouttonSelectione(bouttons);
    if(b!=3)
    {
        SDL_SetRenderDrawColor(rend,243,156,18,255);
        SDL_RenderFillRect(rend,&bouttons[b]);
    }
    SDL_Rect cadre;
    for(int i=0;i<4;i++)
    {
        cadre = ajusterText(bouttons[i],text[i]);
        SDL_RenderCopy(rend,text[i],NULL,&cadre);
    }
    SDL_RenderPresent(rend);
}

// ajuste le rectangle ou va s'afficher le text
SDL_Rect ajusterText(SDL_Rect rect,SDL_Texture* text)
{
    SDL_Rect cadre;
    SDL_QueryTexture(text,NULL,NULL,&cadre.w,&cadre.h);
    cadre.w = cadre.w*rect.h/cadre.h;
    cadre.h = rect.h;
    cadre.y = rect.y;
    cadre.x = rect.x+rect.w/2-cadre.w/2;
    return cadre;
}

// determine quel boutton est selectione
int bouttonSelectione(SDL_Rect rect[])
{
    int curseurx,curseury;
    SDL_GetMouseState(&curseurx,&curseury);
    for(int i=0;i<3;i++)
    {
        if(curseurx>rect[i].x && curseurx<rect[i].x+rect[i].w && curseury>rect[i].y && curseury<rect[i].y+rect[i].h)
            return i;
    }
    return 3;
}

// affiche le score a l'utilisateur et demande de le sauvegarder
void votreScore(int score,int* stop)
{
    int sortir = 0;
    while(!*stop)
    {
        // process events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                *stop = 1;
            }
            if(event.type == SDL_KEYDOWN)
                sortir = 1;
        }
        if(sortir)
            break;
        SDL_SetRenderDrawColor(rend,241,196,15,255);
        SDL_RenderClear(rend);
        afficherText("Votre score est :",20,100,4);
        char scores[10];
        sprintf(scores, "%d",score);
        afficherText(scores,300,250,4);
        SDL_RenderPresent(rend);
    }
}
