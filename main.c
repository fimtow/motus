#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

int main()
{
    int taille = 6;
    char mot[taille+1];
    strcpy(mot,"manger");
    char evaluation[taille+1];
    initializer_evalu(evaluation,'F',taille);
    char input[taille+1];
    printf("Essayez de deviner un mot de %d lettres !\n",taille);
    char vrai[taille+1];
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
