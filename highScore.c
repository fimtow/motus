#include <stdio.h>
#include <stdlib.h>
#include "highScore.h"
void chargerHighScore(char* p ,highScore* m)
{
    FILE* f = fopen(p,"r");
    int i=0;

    while(!feof(f))
    {

        fscanf(f,"%s %d",m[i].nom,&m[i].sc);
        i++;


    }
    fclose(f);
}
void sauvegarderHighScore(char* m,char* nom,int score)
{
     FILE* f=fopen(m,"a");
     fprintf(f,"%s %d \n",nom,score);

    fclose(f);
}
