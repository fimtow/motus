
int choisirNbrLettres();// move to mots.h
void comparer(char input[],char mot[],char *evaluation,int taille);
void initializerMot(char mot[],char vf,int taille);
void genererMot(char mot[],int taille);
void afficherAide(char mot[],int taille);
int motValable(char input[],int taille,char premierChar);
char* dictionnaireUtilise(int taille);// move to mots.h
