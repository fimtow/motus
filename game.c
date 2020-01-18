#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

void comparer(char input[],char mot[],char evaluation[],int taille)
{
    for(int i=0;i<taille;i++)
    {
        if(input[i] == mot[i])
            evaluation[i] = 'V';
        else
            evaluation[i] = 'F';
    }
    char tab[taille+1];
    strcpy(tab,evaluation);
    for(int i=0;i<taille;i++)
    {
        if(evaluation[i] == 'F')
        {
            for(int j=0;j<taille;j++)
            {
                if(tab[j] == 'F' && input[i] == mot[j])
                {
                    evaluation[i] = 'P';
                    tab[j] = 'F';
                }
            }
        }
    }
}

void initializer_evalu(char evalu[],char vf,int taille)
{
    for(int i=0;i<taille;i++)
    {
        evalu[i] = vf;
    }
}

void generermot(char mot[],int taille)
{
    srand(time(NULL));
    int r = rand()%10;

    char* liste[taille];
    FILE* f = fopen("mots.txt","r");

    int c=0;

    while(!feof(f)&& c!=r)
    {
        fscanf(f,"%s",liste);
        c++;
    }
    fclose(f);
    strcpy(mot,liste);

}
