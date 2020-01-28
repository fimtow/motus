// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

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
#include "parametre.h"
#include "highScore.h"

//demare le jeux
void jeux(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font,options* mesOptions,int* stop)
{
    // initialisation de l'etat du jeux
    //etatJeux* monEtat = (etatJeux*)malloc(sizeof(etatJeux));
    etatJeux varMonEtat;
    etatJeux* monEtat = &varMonEtat;
    initializerEtatJeux(monEtat,mesOptions);
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
        lettre = 95;
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
            else if(event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_DELETE || event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) && monEtat->curseur != 0)
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
        miseAjour(lettre,monEtat,dictionnaire,nbr,mesOptions);

        // mise a jour de l'etat de la partie
        changerEtat(monEtat,mesOptions,&dictionnaire,&nbr);
        if(monEtat->etatPartie == PERDU)
         {
             break;
         }
        // affichage et render
        afficher(rectangles,rend,monEtat,lettres,rondJaune,font);

        // ajustement du FPS
        SDL_Delay(1000/60);

    }
    //SDL_StopTextInput();
    SDL_DestroyTexture(rondJaune);
    for(int i=0;i<26;i++)
        SDL_DestroyTexture(&lettres[i]);
    if(!*stop)
        votreScore(monEtat->score,stop,monEtat->mot,mesOptions->difficulte);
    free(monEtat);
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
    bouttons[3].w /= 8;
    bouttons[3].h /= 8;
    bouttons[3].x = LARGEUR/2-bouttons[3].w/2;
    bouttons[3].y = 50;
    SDL_Colour blanc = {255,255,255,255};
    surface = TTF_RenderText_Blended(font,"Jouer",blanc);
    text[0] = SDL_CreateTextureFromSurface(rend,surface);
    surface = TTF_RenderText_Blended(font,"Hight Score",blanc);
    text[1] = SDL_CreateTextureFromSurface(rend,surface);
    surface = TTF_RenderText_Blended(font,"Options",blanc);
    text[2] = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
}

// affiche le menu principal
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
    for(int i=3;i<4;i++)
    {
        cadre = ajusterText(bouttons[i],text[i]);
        SDL_RenderCopy(rend,text[i],NULL,&cadre);
    }
    afficherText2("Jouer",0,BOUTTONY,40,255,255,255,255);
    afficherText2("HighScores",0,BOUTTONY+(BOUTTONH+BOUTTOND),40,255,255,255,255);
    afficherText2("Options",0,BOUTTONY+(BOUTTONH+BOUTTOND)*2,40,255,255,255,255);
    //afficherText("Réalisé par BELGRID YOUNES & AZROUR ABDESSAMAD",75,450,1);
    afficherText2("Jeux réalisé par BELGRID YOUNES & AZROUR ABDESSAMAD",40,450,20,255,255,255,255);
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
void votreScore(int score,int* stop,char mot[],int diff)
{
    highScore tableau[7];
    for(int i=0;i<7;i++)
        tableau[i].sc = -1;
    chargerHighScore(tableau,diff+1);
    int ajouter = 0;
    int i=0;
    while(i<7)
    {
        if(tableau[i].sc == -1 || score>tableau[i].sc)
        {
            ajouter = 1;
            break;
        }
        i++;
    }
    int sortir = 0;
    if(ajouter)
    {
        SDL_StartTextInput();
    }
    char nom[20];
    nom[0] = '_';
    nom[1] = '\0';
    int curseur = 0;
    char lettreUtf8[32];
    char lettre = 48;
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
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                if(ajouter)
                    sauvegarderHighScore(nom,score,diff+1);
                sortir = 1;
            }
            else if(event.type == SDL_KEYDOWN && (event.key.keysym.scancode == SDL_SCANCODE_DELETE || event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) && curseur>0)
            {
                curseur--;
                nom[curseur] = '\0';
            }
            else if(event.type == SDL_TEXTINPUT && curseur < 20)
            {
                strcpy(lettreUtf8,event.text.text);
                lettre = utf8EnAscii(lettreUtf8);
                nom[curseur] = lettre;
                nom[curseur+1] = '\0';
                curseur++;
            }
        }
        if(sortir)
            break;
        SDL_SetRenderDrawColor(rend,241,196,15,255);
        SDL_RenderClear(rend);
        //afficherText("le mot est :",20,0,3);
        afficherText2("le mot est :",0,30,50,255,255,255,255);
        //afficherText(mot,330,0,3);
        afficherText2(mot,0,85,50,255,255,255,255);
        //afficherText("Votre score est :",20,100,4);
        afficherText2("Votre score est :",0,150,60,255,255,255,255);
        char scores[10];
        sprintf(scores, "%d",score);
        //afficherText(scores,300,200,4);
        afficherText2(scores,0,225,60,255,255,255,255);
        if(ajouter)
        {
            //afficherText("Entrer votre nom :",50,300,3);
            afficherText2("Entrer votre nom :",0,300,60,255,255,255,255);
            //afficherText(nom,160,380,3);
            afficherText2(nom,0,380,60,255,255,255,255);
        }
        SDL_RenderPresent(rend);
    }
}

// affiche le menu des options, qui permet de regler les parametres du jeux
void menuOptions(options* mesOptions,int* stop)
{
    int t[4];
    chargerParametre("options.motus",t);
    char difficulte[3][10];
    strcpy(&difficulte[0][0],"facile");
    strcpy(&difficulte[1][0],"moyen");
    strcpy(&difficulte[2][0],"difficile");
    char nbrLettres[5][3];
    strcpy(&nbrLettres[0][0],"6");
    strcpy(&nbrLettres[1][0],"7");
    strcpy(&nbrLettres[2][0],"8");
    strcpy(&nbrLettres[3][0],"9");
    strcpy(&nbrLettres[4][0],"10");
    char son[2][4];
    strcpy(&son[0][0],"ON");
    strcpy(&son[1][0],"OFF");
    char tempsReflexion[3][3];
    strcpy(&tempsReflexion[0][0],"10");
    strcpy(&tempsReflexion[1][0],"15");
    strcpy(&tempsReflexion[2][0],"20");
    int sortir = 0;
    int clique;
    while(!*stop)
    {
        // process events
        SDL_Event event;
        clique = 0;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                *stop = 1;
            }
            else if(event.type == SDL_KEYDOWN)
                sortir = 1;
            else if(event.type == SDL_MOUSEBUTTONDOWN)
                clique = 1;
        }
        if(sortir)
            break;
        SDL_SetRenderDrawColor(rend,241,196,15,255);
        SDL_RenderClear(rend);
        //afficherText("Options",100,10,5);
        afficherText2("Options",0,30,50,255,255,255,255);
        //afficherText("Difficulté",10,130,3);
        afficherText2("Difficulté",10,130,40,255,255,255,255);
        afficherParametres(difficulte,3,10,&t[0],335,140,170,50,clique);
        //afficherText("Nbr lettres",10,190,3);
        afficherText2("Nbr lettres",10,190,40,255,255,255,255);
        afficherParametres(nbrLettres,5,3,&t[1],335,200,170,50,clique);
        //afficherText("temps",10,250,3);
        afficherText2("temps",10,250,40,255,255,255,255);
        afficherParametres(tempsReflexion,3,3,&t[3],335,260,170,50,clique);
        //afficherText("Sons",10,310,3);
        afficherText2("Sons",10,310,40,255,255,255,255);
        afficherParametres(son,2,4,&t[2],335,320,170,50,clique);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);
    }
    if(!*stop)
    {
        sauvegarderParametre("options.motus",t[0],t[1] ,t[2],t[3] );
        affecterOptions(mesOptions);
    }
}

// affiche le menu du high score
void menuHighscore(int* stop,int diff)
{
    int sortir = 0;
    highScore tableau[7];
    for(int i=0;i<7;i++)
        tableau[i].sc = -1;
    chargerHighScore(tableau,diff+1);
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
            else if(event.type == SDL_KEYDOWN)
                sortir = 1;
        }
        if(sortir)
            break;
        SDL_SetRenderDrawColor(rend,241,196,15,255);
        SDL_RenderClear(rend);
        //afficherText("Highscore",100,0,5);
        afficherText2("HighScores :",0,10,50,255,255,255,255);
        int i=0;
        while(tableau[i].sc != -1 && i<7)
        {
            //afficherText(tableau[i].nom,10,100+50*i,3);
            afficherText2(tableau[i].nom,30,100+50*i,40,255,255,255,255);
            char score[10];
            sprintf(score, "%d",tableau[i].sc);
            //afficherText(score,500,100+50*i,3);
            afficherText2(score,450,100+50*i,40,255,255,255,255);
            i++;
        }
        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);
    }
}
