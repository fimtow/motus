// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

#include <stdio.h>
#include <stdlib.h>
#include "highScore.h"

// charge le fichier highscore et mot son contenu dans un tableau
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

// sauvegarde le nouveau high score dans le fichier highScore
void sauvegarderHighScore(char* nom,int score,int diff)
{   char m[16];
    switch(diff)
    {
        case 1: strcpy(m,"highScore/1.txt"); break;
        case 2: strcpy(m,"highScore/2.txt"); break;
        case 3: strcpy(m,"highScore/3.txt"); break;
    }
    highScore tableau[7];
    for(int i=0;i<7;i++)
        tableau[i].sc = -1;
    chargerHighScore(tableau,diff);
    for(int i=6;i>-1;i--)
    {
        if(score<=tableau[i].sc)
            break;
        if(i!=6)
        {
            tableau[i+1].sc = tableau[i].sc;
            strcpy(&tableau[i+1].nom,tableau[i].nom);
        }
        tableau[i].sc = score;
        strcpy(&tableau[i].nom,nom);
    }
    FILE* f = fopen(m,"w");
    int i = 0;
    while(i<7 && tableau[i].sc != -1)
    {
        fprintf(f,"%s %d \n",tableau[i].nom,tableau[i].sc);
        i++;
    }
    fclose(f);
}
