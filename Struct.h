struct Squelette_Player { //Information du joueur
    int life;
    int nb_key;
    int pos_x;
    int pos_y;
    int coins;
    int cabane_coins;
    int J_buissons;
};

typedef struct Squelette_Player s_player;

void init_player(s_player *Joueur) {
    //Création du joueur
    Joueur->life = 5;
    Joueur->nb_key = 0;
    Joueur->coins = 0;
    Joueur->cabane_coins = 0;
    Joueur->J_buissons = 0;
    
    
}