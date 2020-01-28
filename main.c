// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "jeux.h"
#include "mots.h"
#include "menu.h"
#include "gui.h"
#include "parametre.h"

int main(int argc, char** argv)
{
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow( hWnd, SW_HIDE );
    // initialisation de SDL
    initializerSDL(&win,&rend,&font);
    SDL_Surface* icone = IMG_Load("ressources/icone.ico");
    SDL_SetWindowIcon(win,icone);

    // charger les options
    options* mesOptions = (options*)malloc(sizeof(options));
    affecterOptions(mesOptions);

    // initialisation de variables son et des boutons et de l'image
    int changementSon = !mesOptions->son;
    SDL_Rect bouttons[4];
    SDL_Texture* text[4];
    initializerMenu(bouttons,text,font,rend);

    // gameloop
    int stop = 0;
    while(!stop)
    {
        // faire marcher ou pas le generique selon les parametres
        if(mesOptions->son == 1)
            Mix_HaltMusic();
        else if(changementSon != mesOptions->son)
            Mix_PlayMusic(generique,-1);
        changementSon = mesOptions->son;

        // gestion des evenements
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                stop = 1;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int b = bouttonSelectione(bouttons);
                if(mesOptions->son == 0)
                    Mix_PlayChannel(1,clique,0);
                switch(b)
                {
                    case 0 :jeux(win,rend,font,mesOptions,&stop);break;
                    case 1 :menuHighscore(&stop,mesOptions->difficulte);break;
                    case 2 :menuOptions(mesOptions,&stop);break;
                }
            }
        }
        if(stop)
            break;

        // affichage et render
        afficherMenu(win,rend,bouttons,text);

        // attente pour avoir 60 FPS
        SDL_Delay(1000/60);
    }

    // nettoyage et fermeture de SDL
    free(mesOptions);
    for(int i=0;i<4;i++)
        SDL_DestroyTexture(&text[i]);
    fermerSDL(win,rend,font);
    printf("fermeture correcte");
    return 0;
}
