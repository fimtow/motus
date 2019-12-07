#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main()
{
    char mot[5] = "test";
    char evaluation[5] = "FFFF";
    char input[5];
    printf("Essayez de deviner un mot de 4 lettres !\n");
    while(strcmp(evaluation,"VVVV") != 0)
    {
        scanf("%s",input);
        comparer(input,mot,evaluation);
        printf("%s\n",evaluation);
    }
    printf("Vous avez gagne ! cliquez sur n'importe quelle touche pour quitter !");
    getchar();
    return 0;
}
