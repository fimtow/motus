#define HAUTEUR 480
#define LARGEUR 640
#define POSGRILLEX 50
#define POSGRILLEY 50
#define DISTGRILLE 5
#define TAILLEGRILLE 50
#define TEMPSEC 15
#define TEMPSREF 60*TEMPSEC
#define TEMPSX 550
#define TEMPSY 50

// valeurs que prend l'etat de la partie
typedef enum etat
{
    ENCOURS,
    PERDU,
}etat;

// structure qui stock l'etat du jeux (tous les infos necessaires pour afficher une frame)
typedef struct etatJeux
{
    int taille;
    int tentative;
    int curseur;
    int tempsReflexion;
    int score;
    char mot[11];
    char decouvert[11];
    char evaluation[7][11];
    char input[7][11];
    etat etatPartie;
}etatJeux;
// initialise SDL et tous les autres biblio associe
void initializerSDL(SDL_Window** win,SDL_Renderer** rend,TTF_Font** font);

// ferme SDL et libere la memoire
void fermerSDL(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font);

// initialise une variable de type etatJeux
void initializerEtatJeux(etatJeux* monEtat,options* mesOptions);

// initialise le tableau de rectangles qui constitue la grille de jeux selon la taille des mots
void grille(SDL_Rect rectangles[],int taille);

// affiche et render tous les objets
void afficher(SDL_Rect rectangles[],SDL_Renderer* rend,etatJeux* monEtat,SDL_Texture* lettres[],SDL_Texture* rondJaune,TTF_Font *font);

// charge les textures des lettre et du rond jaune
void initializerTextures(SDL_Renderer* rend,SDL_Texture** rondJaune,SDL_Texture* lettres[],TTF_Font *font);

// change l'etat de la partie en cas de perte ou victoire
void changerEtat(etatJeux* monEtat,options* mesOptions);

// convertie un caractere utf8 en ascci en enlevant tous les cracteres non desire
char utf8EnAscii(char utf8[]);

// mise a jour de l'etat du jeux
void miseAjour(char lettre,etatJeux* monEtat,char** dictionnaire,int tailleDictio);

// affiche a chaque tentative un aide(la premiere fois la premiere lettre et une autre au hazard, et par la suite les lettres decouvertes)
void afficherAide(etatJeux* monEtat);


