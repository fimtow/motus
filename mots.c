#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mots.h"
void genererMot(char mot[],int taille)
{
    srand(time(NULL));
    int r = rand()%10;
    char* liste[taille+1];
    FILE* f = fopen(dictionnaireUtilise(taille,1),"r");

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

char* dictionnaireUtilise(int taille,int dif)
{
    switch(taille)
    {
        case 6:return ("dictionnaire/mots.txt");
        case 7:return ("dictionnaire/mots7.txt");
        case 8:return ("dictionnaire/mots8.txt");
        case 9:return ("dictionnaire/mots9.txt");
        case 10:return ("dictionnaire/mots10.txt");
    }


}


void chargerDictionnaire(char dictio[])
{
    //besoin d'un meilleur dictionnaire qui ne contientpas les mots compose et sans accents pour l'instant j'utilise le testdictionnaire.txt
    FILE* f = fopen("dictionnaire/testdictionnaire.txt","r");
    int c=0;

    while(!feof(f))
    {
        // ya probleme ici
        fscanf(f,"%s",&dictio[c*30]);
        c++;
    }
    fclose(f);
}
