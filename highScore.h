// AUTEURS : BELGRID YOUNES & AZROUR ABDESSAMAD

typedef struct highScore
{
    char nom[20];
    int sc;
}highScore;

// charge le fichier highscore et mot son contenu dans un tableau
void chargerHighScore(highScore* t,int diff);

// sauvegarde le nouveau high score dans le fichier highScore
void sauvegarderHighScore(char* nom,int score,int diff);
