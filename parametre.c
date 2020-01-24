#include <stdio.h>
#include <stdlib.h>
#include "parametre.h"
void chargerParametre(char* m,int* t)
{
    FILE* f = fopen(m,"r");
    int i=0;

    while(!feof(f) && i<4)
    {

        fscanf(f,"%d",&t[i]);
        i++;


    }
    fclose(f);
}
void sauvegarderParametre(char* m,int difficulte,int nombresLettres ,int sons,int temps  )
{
     FILE* f=fopen(m,"w");
     fprintf(f,"%d %d %d %d\n",difficulte,nombresLettres,sons,temps);

    fclose(f);
}
