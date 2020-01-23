#define BOUTTONH 50
#define BOUTTONL 250
#define BOUTTONY 250
#define BOUTTOND 10

typedef struct options
{
    int tailleMot;
    int tempsReflexion;
    int difficulte;
}options;
//demare le jeux
void jeux(SDL_Window* win,SDL_Renderer* rend,TTF_Font *font,options* mesOptions,int* stop);

// initialise les rectangles et textures du menu
void initializerMenu(SDL_Rect bouttons[],SDL_Texture* text[],TTF_Font *font,SDL_Renderer* rend);

// affiche le menu
void afficherMenu(SDL_Window* win,SDL_Renderer* rend,SDL_Rect bouttons[],SDL_Texture* text[]);

// ajuste le rectangle ou va s'afficher le text
SDL_Rect ajusterText(SDL_Rect rect,SDL_Texture* text);

// determine quel boutton est selectione
int bouttonSelectione(SDL_Rect rect[]);

void votreHighscore(int score,int* stop);
