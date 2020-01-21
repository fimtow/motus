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
    //char dictionnaire[DICTIO][30];
    //chargerDictionnaire(dictionnaire);


    SDL_Window* win;
    SDL_Renderer* rend;
    TTF_Font *font;
    initializerSDL(&win,&rend,&font);


    // game state
    etatJeux* monEtat = (etatJeux*)malloc(sizeof(etatJeux));

    initializerEtatJeux(monEtat);

    // a refaire afficherAide(mot,taille);
    // initialisation des textures et rectangles
    SDL_Rect rectangles[monEtat->taille*7];
    grille(rectangles,monEtat->taille);


    SDL_Texture* lettres[26];
    SDL_Texture* rondJaune;
    initializerTextures(rend,&rondJaune,lettres,font);



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
            else if(event.type == SDL_TEXTINPUT)
            {
                strcpy(lettreUtf8,event.text.text);
                lettre = utf8EnAscii(lettreUtf8);
                //printf("%s",lettreUtf8);
                //printf("%c",lettre);
            }
        }
        miseAjour(lettre,monEtat);
        afficher(rectangles,rend,monEtat,lettres);
        SDL_Delay(1000/60);
    }

    fermerSDL(win,rend,font);

    return 0;
}
