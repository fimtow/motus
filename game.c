#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void comparer(char input[5],char mot[5],char *evaluation)
{
    for(int i=0;i<4;i++)
    {
        if(input[i] == mot[i])
            evaluation[i] = 'V';
        else
            evaluation[i] = 'F';
    }
}
