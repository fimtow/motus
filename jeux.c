#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeux.h"

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

void initializerMot(char mot[],char vf,int taille)
{
    for(int i=0;i<taille;i++)
    {
        mot[i] = vf;
    }
}

void afficherAide(char mot[],int taille)
{
    srand(time(NULL));
    int r = rand()%(taille-1);
    char aide[taille+1];
    aide[taille] = '\0';
    initializerMot(aide,'*',taille);
    aide[0] = mot[0];
    aide[1+r] = mot[1+r];
    printf("%s\n",aide);
}

int motValable(char input[],int taille,char premierChar,char dictio[])
{
    if((input[0] != premierChar) || strlen(input)<taille)
        return 0;
    // recherche dichotomique du mot dans le dictionnaire
    int binf = 0;
    int bsup = DICTIO-1;
    int moy = (bsup+binf)/2;

    while(binf<=bsup && strcmp(dictio+moy*30,input) != 0)
    {

        if(strcmp(dictio+moy*30,input)<0)
            binf = moy+1;
        else
            bsup = moy-1;
        moy = (bsup+binf)/2;
    }
    if(strcmp(dictio+moy*30,input) == 0)
        return 1;
    else
        return 0;
}
// move to mots.h
void genererMot(char mot[],int taille)
{
    srand(time(NULL));
    int r = rand()%10;
    char* liste[taille+1];
    FILE* f = fopen(dictionnaireUtilise(taille),"r");

    int c=0;

    while(!feof(f)&& c<r+1)
    {
        fscanf(f,"%s\n",liste);
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

// move to mots.c
void chargerDictionnaire(char dictio[])
{
    //besoin d'un meilleur dictionnaire qui ne contientpas les mots compose et sans accents pour l'instant j'utilise le testdictionnaire.txt
    FILE* f = fopen("testdictionnaire.txt","r");
    int c=0;

    while(!feof(f))
    {
        fscanf(f,"%s",dictio+30*c);
        c++;
    }
    fclose(f);
}
