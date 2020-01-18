#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


int main()
{
    int taille = choisir_le_nombre_des_lettres();
    char mot[taille];
    generermot(mot,taille);
    char evaluation[taille];
    initializer_evalu(evaluation,'F',taille);
    char input[taille];
    printf("Essayez de deviner un mot de %d lettres !\n",taille);
    char vrai[taille];
    initializer_evalu(vrai,'V',taille);
    while(strcmp(evaluation,vrai) != 0)
    {
        scanf("%s",input);
        comparer(input,mot,evaluation,taille);
        printf("%s\n",evaluation);
    }
    printf("Vous avez gagne ! cliquez sur n'importe quelle touche pour quitter !");
    getchar();
    return 0;
}
