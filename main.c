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

    // initialisation de SDL
    SDL_Window* win;
    SDL_Renderer* rend;
    TTF_Font *font;
    initializerSDL(&win,&rend,&font);


    // initialisation de l'etat du jeux
    etatJeux* monEtat = (etatJeux*)malloc(sizeof(etatJeux));
    initializerEtatJeux(monEtat);
    printf("%s",monEtat->mot);


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
        miseAjour(lettre,monEtat,dictionnaire);

        // affichage et render
        afficher(rectangles,rend,monEtat,lettres,rondJaune,font);

        // mise a jour de l'etat de la partie
        changerEtat(monEtat);
        // ajustement du FPS
        SDL_Delay(1000/60);

    }
    // nettoyage et fermeture de SDL
    fermerSDL(win,rend,font);

    return 0;
}
