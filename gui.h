#define HAUTEUR 480
#define LARGEUR 640
#define POSGRILLEX 50
#define POSGRILLEY 50
#define DISTGRILLE 5
#define TAILLEGRILLE 50

typedef enum etat
{
    ENCOURS,
    GAGNE,
    PERDU,
}etat;

typedef struct etatJeux
{
    int taille;
    int tentative;
    int curseur;
    char mot[11];
    char evaluation[7][11];
    char input[7][11];
    etat etatPartie;
}etatJeux;
void initializerSDL(SDL_Window** win,SDL_Renderer** rend,TTF_Font** font);
void fermerSDL(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font);
void initializerEtatJeux(etatJeux* monEtat);
void grille(SDL_Rect rectangles[],int taille);
void afficher(SDL_Rect rectangles[],SDL_Renderer* rend,etatJeux* monEtat,SDL_Texture* lettres[]);
void initializerTextures(SDL_Renderer* rend,SDL_Texture** rondJaune,SDL_Texture* lettres[],TTF_Font *font);
void changerEtat(etatJeux* monEtat);
char utf8EnAscii(char utf8[]);
void miseAjour(char lettre,etatJeux* monEtat);

