// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mots.h"

// permet de generer un mot aleatoire
void genererMot(char mot[],int taille,int diff)
{   int mod=modulo(taille,diff);
    srand(time(NULL));
    int r = rand()%mod;
    char liste[taille+1];
    FILE* f = fopen(dictionnaireUtilise(taille,diff),"r");
    int c=0;
    while(!feof(f)&& c<r+1)
    {
        fscanf(f,"%s\n",liste);
        c++;
    }
    fclose(f);
    strcpy(mot,liste);
}

// permet de savoir quel fichier dictionnaire utilise pour chaque taille et difficulte
char* dictionnaireUtilise(int taille,int dif)
{
    if(dif==1)
    {
        switch(taille)
        {
            case 6:return ("dictionnaire/facile/6.txt");
            case 7:return ("dictionnaire/facile/7.txt");
            case 8:return ("dictionnaire/facile/8.txt");
            case 9:return ("dictionnaire/facile/9.txt");
            case 10:return ("dictionnaire/facile/10.txt");
        }
    }
    if(dif==2)
    {
        switch(taille)
        {
            case 6:return ("dictionnaire/moyen/6.txt");
            case 7:return ("dictionnaire/moyen/7.txt");
            case 8:return ("dictionnaire/moyen/8.txt");
            case 9:return ("dictionnaire/moyen/9.txt");
            case 10:return ("dictionnaire/moyen/10.txt");
        }
    }
    if(dif==3)
    {
        switch(taille)
        {
            case 6:return ("dictionnaire/difficile/6.txt");
            case 7:return ("dictionnaire/difficile/7.txt");
            case 8:return ("dictionnaire/difficile/8.txt");
            case 9:return ("dictionnaire/difficile/9.txt");
            case 10:return ("dictionnaire/difficile/10.txt");
        }
    }

}

// permet de lire le fichier dictionnaire et charger son contenu dans un tableau
void chargerDictionnaire(char** dictio,char a)
{   char m[18];
    strcpy(m,"dictionnaire/x.txt");
    m[13]=a;
    char temp[11];
    FILE* f = fopen(m,"r");
    int c=0;
    while(!feof(f))
    {
        fscanf(f,"%s",temp);
        strcpy(dictio[c],temp);
        c++;
    }
    fclose(f);
}

// permet de determiner la taille du dictionnaire pour faire l'allocation dynamique adequate du tableau qui va le contenir
int tailleDictionnaire(char a)
{
    switch(a)
    {
        case 'a': return 13451;
        case 'b': return 9331;
        case 'c': return 17356;
        case 'd': return 16780;
        case 'e': return 18347;
        case 'f': return 7554;
        case 'g': return 6259;
        case 'h': return 3114;
        case 'i': return 4944;
        case 'j': return 1672;
        case 'k': return 284;
        case 'l': return 4779;
        case 'm': return 9039;
        case 'n': return 2292;
        case 'o': return 3171;
        case 'p': return 13961;
        case 'q': return 493;
        case 'r': return 17125;
        case 's': return 11090;
        case 't': return 8285;
        case 'u': return 590;
        case 'v': return 4352;
        case 'w': return 107;
        case 'x': return 43;
        case 'y': return 64;
        case 'z': return 560;
    }
}

// permet de recharger le dictionnaire dans le tableau, pour cela elle utilise les fonctions precedentes
char** initializerDictionnaire(char** dictionnaire,char lettre,int* nbr)
{
    *nbr=tailleDictionnaire(lettre);
    dictionnaire= (char **)malloc(*nbr*sizeof(char *)) ;
    for (int i=0 ; i<*nbr ; i++)
        dictionnaire[i] = (char *)malloc(11*sizeof(char)) ;
    chargerDictionnaire(dictionnaire,lettre);
    return dictionnaire;
}

// retourne le nombre de mots dans le fichier utlise pour la generation du mot (selon difficulte et taille)
int modulo(int taille,int diff)
{
    if(diff==1)
    {
        switch(taille)
        {
            case 6:return 431;
            case 7:return 425;
            case 8:return 358;
            case 9:return 253;
            case 10:return 143;
        }
    }
    if(diff==2)
    {
        switch(taille)
        {
            case 6:return 913;
            case 7:return 841;
            case 8:return 187;
            case 9:return 184;
            case 10:return 113;
        }
    }
    if(diff==3)
    {
        switch(taille)
        {
            case 6:return 71;
            case 7:return 144;
            case 8:return 200;
            case 9:return 139;
            case 10:return 130;
        }
    }
}
