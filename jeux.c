#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeux.h"

// la fonction principale au fonctionnement du jeux, elle compare l'input au mot et retourne une evaluation
void comparer(char input[],char mot[],char evaluation[],int taille)
{
    // premier traitement V ou F
    for(int i=0;i<taille;i++)
    {
        if(input[i] == mot[i])
            evaluation[i] = 'V';
        else
            evaluation[i] = 'F';
    }
    // deuxieme traitement pour localiser les P
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

// fonction qui recoit un mot ,un char et sa taille, elle remplie le mot de ce char
void initializerMot(char mot[],char vf,int taille)
{
    for(int i=0;i<taille;i++)
    {
        mot[i] = vf;
    }
    mot[taille] = '\0';
}

// verifie si l'input et un mot valable (a la meme nombre de lettres,la meme premiere lettre, fait partie du dictionnaire francais etc..)
int motValable(char input[],int taille,char premierChar,char** dictio,int tailleDictio)
{
    if((input[0] != premierChar) || strlen(input)<taille)
        return 0;
    // recherche dichotomique du mot dans le dictionnaire
    int binf = 0;
    int bsup = tailleDictio-1;
    int moy = (bsup+binf)/2;

    while(binf<=bsup && strcmp(dictio[moy],input) != 0)
    {

        if(strcmp(dictio[moy],input)<0)
            binf = moy+1;
        else
            bsup = moy-1;
        moy = (bsup+binf)/2;
    }
    if(strcmp(dictio[moy],input) == 0)
        return 1;
    else
        return 0;
}




