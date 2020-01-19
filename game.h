// taille du dictionnare (nbr des lignes) ,pour testdictionnaire.txt le nbr est 16
#define DICTIO  16
int choisirNbrLettres();// move to mots.h
void comparer(char input[],char mot[],char *evaluation,int taille);
void initializerMot(char mot[],char vf,int taille);
void genererMot(char mot[],int taille);
void afficherAide(char mot[],int taille);
int motValable(char input[],int taille,char premierChar,char dictio[]);
void chargerDictionnaire(char dictio[]);
char* dictionnaireUtilise(int taille);// move to mots.h
