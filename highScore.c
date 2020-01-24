#include <stdio.h>
#include <stdlib.h>
#include "highScore.h"
void chargerHighScore(highScore* t,int diff)
{
     char m[16];
    switch(diff)
    {
        case 1: strcpy(m,"highScore/1.txt"); break;
        case 2: strcpy(m,"highScore/2.txt"); break;
        case 3: strcpy(m,"highScore/3.txt"); break;

    }
    int i=0;
    FILE* f = fopen(m,"r");
    while(!feof(f))
    {

        fscanf(f,"%s %d",t[i].nom,&t[i].sc);
        i++;


    }
    fclose(f);
}
void sauvegarderHighScore(char* nom,int score,int diff)
{   char m[16];
    switch(diff)
    {
        case 1: strcpy(m,"highScore/1.txt"); break;
        case 2: strcpy(m,"highScore/2.txt"); break;
        case 3: strcpy(m,"highScore/3.txt"); break;

    }
      FILE* f = fopen(m,"a");
     fprintf(f,"%s %d \n",nom,score);

    fclose(f);
}
