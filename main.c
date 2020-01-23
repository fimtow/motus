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


int main(int argc, char** argv)
{

    // initialisation de SDL
    SDL_Window* win;
    SDL_Renderer* rend;
    TTF_Font *font;
    initializerSDL(&win,&rend,&font);

    // initialisation des rectangles et textures
    options* mesOptions = (options*)malloc(sizeof(options));
    SDL_Rect bouttons[4];
    SDL_Texture* text[4];
    initializerMenu(bouttons,text,font,rend);

    // gameloop
    int stop = 0;
    while(!stop)
    {
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
                switch(b)
                {
                    case 0 :jeux(win,rend,font,mesOptions,&stop);break;
                    case 1 :printf("hightscore");break;
                    case 2 :printf("options");break;
                }
            }
        }
        if(stop)
            break;
        // affichage et render
        afficherMenu(win,rend,bouttons,text);
        // wait to have 60 fps
        SDL_Delay(1000/60);
    }

    // nettoyage et fermeture de SDL
    fermerSDL(win,rend,font);

    return 0;
}
