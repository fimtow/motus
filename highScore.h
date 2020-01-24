
typedef struct highScore
{
    char nom[20];
    int sc;

}highScore;
void chargerHighScore(highScore* t,int diff);
void sauvegarderHighScore(char* nom,int score,int diff);
