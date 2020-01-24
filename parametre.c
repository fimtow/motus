#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include "menu.h"
#include "parametre.h"

void chargerParametre(char* m,int* t)
{
    FILE* f = fopen(m,"r");
    int i=0;

    while(!feof(f) && i<4)
    {

        fscanf(f,"%d",&t[i]);
        i++;


    }
    fclose(f);
}
void sauvegarderParametre(char* m,int difficulte,int nombresLettres ,int sons,int temps  )
{
     FILE* f=fopen(m,"w");
     fprintf(f,"%d %d %d %d\n",difficulte,nombresLettres,sons,temps);

    fclose(f);
}
void affecterOptions(options* mesOptions)
{
    int t[4];
    chargerParametre("options.motus",t);
    mesOptions->difficulte = t[0];
    mesOptions->tailleMot = t[1]+6;
    mesOptions->tempsReflexion = 10+5*t[3];
    mesOptions->son = t[2];
}
