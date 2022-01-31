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
    int J_cabane;
};

struct Squelette_Monster { //information Monstre
    int pos_x;
    int pos_y;
    int type;
    int NbMonstre;
    char on_object;
};

struct Init_Settings { //Initialisation des settings
    int difficulty;
    int coord[100][100];
};


typedef struct Squelette_Player s_player;   //s_player diminutif de la structure
typedef struct Squelette_Monster s_monster; //s_monster diminutif de la structure
typedef struct Init_Settings i_settings;    //i_settings diminutif de la structure   

void init_player(s_player *Joueur) {
    //Création du joueur
    Joueur->life = 5;
    Joueur->nb_key = 0;
    Joueur->coins = 0;
    Joueur->cabane_coins = 0;
    Joueur->J_buissons = 0;  
    Joueur->J_cabane = 0;
}