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

void initializerEvalu(char evalu[],char vf,int taille)
{
    for(int i=0;i<taille;i++)
    {
        evalu[i] = vf;
    }
}
// move to mots.h
void genererMot(char mot[],int taille)
{
    srand(time(NULL));
    int r = rand()%10;
    char* liste[taille];
    FILE* f = fopen(dictionnaireUtilise(taille),"r");

    int c=0;

    while(!feof(f)&& c!=r)
    {
        fscanf(f,"%s",liste);
        c++;
    }
    fclose(f);

    strcpy(mot,liste);

}

int choisirNbrLettres()
{
    int c;
    do
    {
        printf("choisissez le nombres des lettres entre (6-10)\n");
        scanf("%d",&c);

    }while(c>10 || c<6);
    return c;
}
// move to mots.c
char* dictionnaireUtilise(int taille)
{
    switch(taille)
    {
        case 6:return ("mots.txt");
        case 7:return ("mots7.txt");
        case 8:return ("mots8.txt");
        case 9:return ("mots9.txt");
        case 10:return ("mots10.txt");
    }


}
