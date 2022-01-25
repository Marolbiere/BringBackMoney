struct Squelette_Player { //Information du joueur
    int life;
    int nb_key;
    int pos_x;
    int pos_y;
    int poscab_x;
    int poscab_y;
    int coins;
    int cabane_coins;
    int J_buissons;
};

struct Squelette_Monster { //information Monstre
    int pos_x;
    int pos_y;
    int type;
    int NbMonstre;
    char on_object;
};


typedef struct Squelette_Player s_player;
typedef struct Squelette_Monster s_monster;


void init_player(s_player *Joueur) {
    //Création du joueur
    Joueur->life = 5;
    Joueur->nb_key = 0;
    Joueur->coins = 0;
    Joueur->cabane_coins = 0;
    Joueur->J_buissons = 0;  
}