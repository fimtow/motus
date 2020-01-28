// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

// la fonction principale au fonctionnement du jeux, elle compare l'input au mot et retourne une evaluation
void comparer(char input[],char mot[],char *evaluation,int taille);

// fonction qui recoit un mot ,un char et sa taille, elle remplie le mot de ce char
void initializerMot(char mot[],char vf,int taille);

// verifie si l'input et un mot valable (a la meme nombre de lettres,la meme premiere lettre, fait partie du dictionnaire francais etc..)
int motValable(char input[],int taille,char premierChar,char** dictio,int tailleDictio,char inputTable[],int tentative);


