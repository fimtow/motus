#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "jeux.h"
#include "mots.h"
#include "gui.h"


int main(int argc, char** argv)
{
    // initialisation du dictionnaire
    char dictionnaire[DICTIO][30];
    chargerDictionnaire(dictionnaire);


    SDL_Window* win;
    SDL_Renderer* rend;
    TTF_Font *font;
    initializerSDL(&win,&rend,&font);


    // game state
    etatJeux* monEtat = (etatJeux*)malloc(sizeof(etatJeux));

    initializerEtatJeux(monEtat);
    printf("%s",monEtat->mot);
    // a refaire afficherAide(mot,taille);
    // initialisation des textures et rectangles
    SDL_Rect rectangles[monEtat->taille*7];
    grille(rectangles,monEtat->taille);


    SDL_Texture* lettres[26];
    SDL_Texture* rondJaune;
    initializerTextures(rend,&rondJaune,lettres,font);

    int tempsReflexion = TEMPSREF;
    afficherAide(monEtat);
    // game loop
    while(monEtat->etatPartie == ENCOURS)
    {

        SDL_StartTextInput();
        SDL_Event event;
        char lettreUtf8[32];
        char lettre = 48;

        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                monEtat->etatPartie = PERDU;
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
            {

                if(motValable(&(monEtat->input[monEtat->tentative-1][0]),monEtat->taille,monEtat->mot[0],dictionnaire))
                    comparer(&(monEtat->input[monEtat->tentative-1][0]),monEtat->mot,&(monEtat->evaluation[monEtat->tentative-1][0]),monEtat->taille);
                monEtat->tentative++;
                monEtat->curseur = 0;
                tempsReflexion = TEMPSREF;
                afficherAide(monEtat);

            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_DELETE && monEtat->curseur != 0)
            {
                monEtat->input[monEtat->tentative-1][monEtat->curseur-1] = NULL;
                monEtat->curseur--;
            }
            else if(event.type == SDL_TEXTINPUT)
            {
                strcpy(lettreUtf8,event.text.text);
                lettre = utf8EnAscii(lettreUtf8);
                if(lettreUtf8[0] == 13)
                    printf("lol");
            }
        }
        miseAjour(lettre,monEtat);
        afficher(rectangles,rend,monEtat,lettres,rondJaune);

        changerEtat(monEtat);
        SDL_Delay(1000/60);
        tempsReflexion--;
        if(tempsReflexion<0)
        {
            monEtat->tentative++;
            monEtat->curseur = 0;
            tempsReflexion = TEMPSREF;
        }

    }
    fermerSDL(win,rend,font);

    return 0;
}
