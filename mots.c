#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mots.h"
void genererMot(char mot[],int taille,int mod)
{   mod=100;
    srand(time(NULL));
    int r = rand()%mod;
    char liste[taille+1];
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


void chargerDictionnaire(char** dictio,char a)
{   char m[18];
    strcpy(m,"dictionnaire/x.txt");
    m[13]=a;
    char temp[11];

    //besoin d'un meilleur dictionnaire qui ne contientpas les mots compose et sans accents pour l'instant j'utilise le testdictionnaire.txt
    FILE* f = fopen(m,"r");
    int c=0;

    while(!feof(f))
    {
        // ya probleme ici
        fscanf(f,"%s",temp);

        strcpy(dictio[c],temp);
        c++;
    }
    fclose(f);
}
int tailleDictionnaire(char a)
{
    switch(a)
    {
        case 'a': return 13451;
        case 'b': return 9331;
        case 'c': return 17354;
        case 'd': return 16780;
        case 'e': return 18346;
        case 'f': return 7554;
        case 'g': return 6259;
        case 'h': return 3116;
        case 'i': return 4944;
        case 'j': return 1672;
        case 'k': return 288;
        case 'l': return 4781;
        case 'm': return 9041;
        case 'n': return 2293;
        case 'o': return 3171;
        case 'p': return 13962;
        case 'q': return 493;
        case 'r': return 17126;
        case 's': return 11093;
        case 't': return 8287;
        case 'u': return 590;
        case 'v': return 4352;
        case 'w': return 112;
        case 'x': return 44;
        case 'y': return 65;
        case 'z': return 560;
    }
}
char** initializerDictionnaire(char** dictionnaire,char lettre,int* nbr)
{
    *nbr=tailleDictionnaire(lettre);
    dictionnaire= (char **)malloc(*nbr*sizeof(char *)) ;
    for (int i=0 ; i<*nbr ; i++)
        dictionnaire[i] = (char *)malloc(11*sizeof(char)) ;
    chargerDictionnaire(dictionnaire,lettre);
    return dictionnaire;
}
int modulo(int taille,int diff)
{
      if(diff==1)
{
    switch(taille)
    {
        case 6:return 163;
        case 7:return 205;
        case 8:return 231;
        case 9:return 177;
        case 10:return 101;
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
