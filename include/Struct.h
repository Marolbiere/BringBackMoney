
//Structure pour un Joueur
struct Squelette_Player { 
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
    char *mess;
};

//Structure pour un Monstre
struct Squelette_Monster {
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

/*------------Diminutif des structures------------*/
typedef struct Squelette_Player  s_player;      
typedef struct Squelette_Monster s_monster;   
typedef struct Init_Settings     i_settings;    
/*------------------------------------------------*/

void init_player(s_player *Joueur) { //Initialisation des variables du Joueur
    Joueur->mess = "";
    Joueur->life = 5;
    Joueur->nb_key = 0;
    Joueur->coins = 0;
    Joueur->cabane_coins = 0;
    Joueur->J_buissons = 0;  
    Joueur->J_cabane = 0;
}
