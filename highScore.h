
typedef struct highScore
{
    char nom[20];
    int sc;

}highScore;
void chargerHighScore(char* f,highScore* t);
void sauvegarderHighScore(char* f,char* nom,int score);

