#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void comparer(char input[5],char mot[5],char evaluation[5])
{
    for(int i=0;i<4;i++)
    {
        if(input[i] == mot[i])
            evaluation[i] = 'V';
        else
            evaluation[i] = 'F';
    }
    char tab[5];
    strcpy(tab,evaluation);
    for(int i=0;i<4;i++)
    {
        if(evaluation[i] == 'F')
        {
            for(int j=0;j<4;j++)
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
