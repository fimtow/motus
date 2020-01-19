#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeux.h"
#include "mots.h"


int main()
{
    // initialisation du dictionnaire
    char dictionnaire[DICTIO][30];
    //nombre de tentative
    int tentative=1;
    chargerDictionnaire(dictionnaire);
    // game state
    int taille = choisirNbrLettres();
    char mot[taille+1];
    genererMot(mot,taille);
    char evaluation[taille+1];
    initializerMot(evaluation,'F',taille);
    char input[taille+1];
    printf("Essayez de deviner un mot de %d lettres !\n",taille);
    afficherAide(mot,taille);
    char vrai[taille+1];
    initializerMot(vrai,'V',taille);
    // game loop
    while(strcmp(evaluation,vrai) != 0 && tentative<=7 )
    {
        scanf("%s",input);
        if(motValable(input,taille,mot[0],dictionnaire))
        {
            comparer(input,mot,evaluation,taille);
            printf("%s\n",evaluation);
        }

        tentative++;
    }
    printf("Vous avez gagne ! cliquez sur n'importe quelle touche pour quitter !");
    getchar();
    return 0;
}
