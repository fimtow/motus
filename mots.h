// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

// permet de generer un mot aleatoire
void genererMot(char mot[],int taille,int diff);

// permet de savoir quel fichier dictionnaire utilise pour chaque taille et difficulte
char* dictionnaireUtilise(int taille,int dif);

// permet de lire le fichier dictionnaire et charger son contenu dans un tableau
void chargerDictionnaire(char** dictio,char a);

// permet de determiner la taille du dictionnaire pour faire l'allocation dynamique adequate du tableau qui va le contenir
int tailleDictionnaire(char a);

// permet de recharger le dictionnaire dans le tableau, pour cela elle utilise les fonctions precedentes
char** initializerDictionnaire(char** dictionnaire,char lettre,int *nbr);

// retourne le nombre de mots dans le fichier utlise pour la generation du mot (selon difficulte et taille)
int modulo(int nbr,int diff);
