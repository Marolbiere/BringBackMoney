#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

void interaction_monstre_joueur(char carte[SIZE_Y][SIZE_X],s_player *Joueur, s_monster TableMonstre[MAX_MONSTER], int i) {
    //Interaction entre monstre et Joueur
    RANDOMIZER_SEED;
    int nb_random_x = alea(2,18);
    int nb_random_y = alea(2,18);
    do {
        TableMonstre[i].pos_x = nb_random_x;
        TableMonstre[i].pos_y = nb_random_y;
    }   while(carte[nb_random_y][nb_random_x] != ' ');
    carte[nb_random_y][nb_random_x] = TableMonstre[i].type + '0';
    if((TableMonstre[i].type == 5 || TableMonstre[i].type == 6 || TableMonstre[i].type == 7 || TableMonstre[i].type == 8) && Joueur->coins>=1)
        Joueur->coins -= 1;
    else {
        Joueur->life -=1;
    }
}

void interaction_joueur_monstre(char carte[SIZE_Y][SIZE_X], s_player *Joueur, s_monster TableMonstre[MAX_MONSTER]) {
    for (int i = 0; i < TableMonstre[0].NbMonstre; i++) {
        if(Joueur->pos_y==TableMonstre[i].pos_y && Joueur->pos_x==TableMonstre[i].pos_x) {
            interaction_monstre_joueur(carte,Joueur,TableMonstre,i);
        }
    } 
}

void mvt_Monstre(char carte[SIZE_Y][SIZE_X], s_monster TableMonstre[MAX_MONSTER], s_player *Joueur, int n_y, int n_x, int i) {
    //Fonction global de mvt du monstre + interaction avec l'environnement
    if(n_y >= 0 && n_y <= SIZE_Y -1 && n_x >= 0 && n_x <= SIZE_X -1) {
        char object = carte[n_y][n_x];
        if(object != 'X' && object != 'H' && object != (TableMonstre[i].type + '0')) {
            if(object=='J') {
                carte[TableMonstre[i].pos_y][TableMonstre[i].pos_x] = ' ';
                interaction_monstre_joueur(carte,Joueur,TableMonstre,i);
                carte[n_y][n_x] = 'J';
            }
            else {
                if(TableMonstre[i].on_object) {
                    carte[TableMonstre[i].pos_y][TableMonstre[i].pos_x] = TableMonstre[i].on_object;
                }
                else if(TableMonstre[i].on_object == 0) {
                    carte[TableMonstre[i].pos_y][TableMonstre[i].pos_x] = ' ';
                }
                carte[n_y][n_x] = TableMonstre[i].type + '0';
                TableMonstre[i].pos_y = n_y;
                TableMonstre[i].pos_x = n_x;
                TableMonstre[i].on_object = object;
            }
        }
    }
}

int * chemin_court(s_monster TableMonstre[MAX_MONSTER],s_player *Joueur, int i, int nb_case) {
    static int Coord[2];
    if(TableMonstre[i].pos_y <= Joueur->pos_y) {
        Coord[0] = TableMonstre[i].pos_y + nb_case;
    }
    if(TableMonstre[i].pos_y >= Joueur->pos_y) {
        Coord[0] = TableMonstre[i].pos_y - nb_case;
    }
    if(TableMonstre[i].pos_x <= Joueur->pos_x) {
        Coord[1] = TableMonstre[i].pos_x + nb_case;
    }
    if(TableMonstre[i].pos_x >= Joueur->pos_x) {
        Coord[1] = TableMonstre[i].pos_x - nb_case;
    }
    return Coord;
}

void Type_Monstre(char carte[SIZE_Y][SIZE_Y], s_monster TableMonstre[MAX_MONSTER], s_player *Joueur) {
    int n_x, n_y;
    int *Coord;
    for (int i = 0; i < TableMonstre[0].NbMonstre; i++) {
            switch (TableMonstre[i].type) {
                case 1: 
                case 5:
                    n_y = TableMonstre[i].pos_y + alea(-1,1);
                    n_x = TableMonstre[i].pos_x + alea(-1,1);
                    mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i);
                    break;
                case 2:
                case 6:
                    n_y = TableMonstre[i].pos_y + alea(-3,3);
                    n_x = TableMonstre[i].pos_x + alea(-3,3);
                    mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i);
                    break;
                case 4:
                case 8:
                    if(Joueur->J_buissons == 1 /*|| Joueur->J_cabane == 1*/) {
                        n_y = TableMonstre[i].pos_y + alea(-3,3);
                        n_x = TableMonstre[i].pos_x + alea(-3,3);
                        mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i); 
                    }
                    else {
                        Coord = chemin_court(TableMonstre,Joueur,i,3);
                        n_y = *(Coord + 0);
                        n_x = *(Coord + 1);
                        mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i); 
                    }
                    break;
                case 3:
                case 7:
                    if(Joueur->J_buissons == 1 /*|| Joueur->J_cabane == 1*/) {
                        n_y = TableMonstre[i].pos_y + alea(-1,1);
                        n_x = TableMonstre[i].pos_x + alea(-1,1);
                        mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i); 
                    }
                    else {
                        Coord = chemin_court(TableMonstre,Joueur,i,1);
                        n_y = *(Coord + 0);
                        n_x = *(Coord + 1);
                        mvt_Monstre(carte,TableMonstre,Joueur, n_y, n_x, i); 
                    }
                    break;
            }
    }
}

void trap(char carte[SIZE_Y][SIZE_X], s_player *Joueur,int new_pos_y, int new_pos_x) {
    RANDOMIZER_SEED;
    int type_trap = alea(1,3);
    int r_y = alea(2,18);
    int r_x = alea(2,18);
    switch (type_trap)
    {
        case 1: //Perdre une vie
            Joueur->life-=1;
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->pos_x = new_pos_x;
            Joueur->pos_y = new_pos_y;
            break;
        case 2: //Retour à la cabane
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = ' ';
            carte[Joueur->poscab_y][Joueur->poscab_x - 1] = 'J';
            Joueur->pos_y = Joueur->poscab_y;
            Joueur->pos_x = Joueur->poscab_x - 1;
            break;
        case 3: //TP aléatoire sur la map
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = ' ';
            while(carte[r_y][r_x] == ' ') {
                carte[r_y][r_x] = 'J';
            }
            Joueur->pos_y = r_y;
            Joueur->pos_x = r_x;
            break;
    }
}

void deplacement(char carte[SIZE_Y][SIZE_X], s_player *Joueur, int new_pos_y, int new_pos_x) {
    if (Joueur->J_buissons == 1) {
        carte[Joueur->pos_y][Joueur->pos_x] = 'G';
        carte[new_pos_y][new_pos_x] = 'J';
        Joueur->J_buissons = 0;
    }
    else {
        carte[Joueur->pos_y][Joueur->pos_x] = ' ';
        carte[new_pos_y][new_pos_x] = 'J';
    }
    
    Joueur->pos_x = new_pos_x;
    Joueur->pos_y = new_pos_y;

}

void interaction_environnement(int new_pos_y, int new_pos_x, char carte[SIZE_X][SIZE_Y], s_player *Joueur, s_monster TableMonstre[MAX_MONSTER]) {
    int r_y,r_x;
    switch (carte[new_pos_y][new_pos_x])
    {
    case 'O': //Pièce
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        do {
            r_y = alea(3,SIZE_Y);
            r_x = alea(3,SIZE_X);
        }while(carte[r_y][r_x] != ' ');
        carte[r_y][r_x] = 'O'; //spawn infini de pièces
        Joueur->coins+=1;
        break;
    case 'G': //Buisson
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        Joueur->J_buissons = 1;
        break;
    case 'C': //Coffre
        if(Joueur->nb_key>=1) {
            //RANDOMIZER_SEED;
            int p_or_c = rand()%SIZE_X;
            if(p_or_c %2 == 0) { Joueur->coins += 1;}
            else               { trap(carte,Joueur,new_pos_y,new_pos_x); }
            deplacement(carte,Joueur,new_pos_y,new_pos_x);
            Joueur-> nb_key -=1;
        }
        break;
    case 'K': //Clé
        Joueur->nb_key+=1;
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        break;
    case 'H':
        interface_cabane(Joueur, carte, new_pos_y, new_pos_x);
        break;
    case 'X': //Obstacle
        break;
    case 'P': //Piège
        trap(carte,Joueur,new_pos_y,new_pos_x);
        break;
    case '1'||'2'||'3'||'4'||'5'||'6'||'7'||'8':
        interaction_joueur_monstre(carte,Joueur,TableMonstre);
    //Cases de bases (espace)
    default:
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        break;
    }
}

void input_player(char carte[SIZE_Y][SIZE_X], s_player *Joueur, s_monster TableMonstre[MAX_MONSTER]) {
    int var_x = 0;
    int var_y = 0;
    char direction = tolower(getch());
    //int var_interaction = 0;
    switch (direction) {
        case 'z': 
            if(Joueur->pos_y != 0) {var_y = -1;}
            break;
        case 'q': 
            if(Joueur->pos_x != 0) {var_x = -1;}
            break;
        case 's':
            if(Joueur->pos_y != SIZE_Y - 1) {var_y = 1;}
            break;
        case 'd': if(Joueur->pos_x != SIZE_X - 1) {var_x = 1;} 
            break;
    }
    
    if(var_x != 0|| var_y != 0) {
        int new_pos_x = Joueur->pos_x + var_x;
        int new_pos_y = Joueur->pos_y + var_y;
        interaction_environnement(new_pos_y,new_pos_x,carte,Joueur, TableMonstre);
    }
}