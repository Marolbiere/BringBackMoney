#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

void interaction_monstre_joueur(char carte[SIZE_Y][SIZE_X],s_player *Joueur, s_monster TableMonstre[MAX_MONSTER], int i) {
    int nb_random_x = alea(2,18);
    int nb_random_y = alea(2,18);
    Joueur->life-=1;
    while(carte[nb_random_y][nb_random_x] == ' ') {
        TableMonstre[i].pos_x = nb_random_x;
        TableMonstre[i].pos_y = nb_random_y;
    }
}

void mvt_Monstre(char carte[SIZE_Y][SIZE_X], s_monster TableMonstre[MAX_MONSTER], int n_y, int n_x, int i) {
    if(n_y >= 0 && n_y <= SIZE_Y -1 && n_x >= 0 && n_x <= SIZE_X -1) {
        char object = carte[n_y][n_x];
        if(object != 'X' && object != 'H' && object != (TableMonstre[i].type + '0')) {
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

void Type_Monstre(char carte[SIZE_Y][SIZE_Y], s_monster TableMonstre[MAX_MONSTER]) {
    int n_x, n_y;
    for (int i = 0; i < TableMonstre[0].NbMonstre; i++)
    {
            switch (TableMonstre[i].type) {
            case 2:
                n_y = TableMonstre[i].pos_y + alea(-3,3);
                n_x = TableMonstre[i].pos_x + alea(-3,3);
                mvt_Monstre(carte,TableMonstre, n_y, n_x, i);
                break;
            default:
                n_y = TableMonstre[i].pos_y + alea(-1,1);
                n_x = TableMonstre[i].pos_x + alea(-1,1);
                mvt_Monstre(carte,TableMonstre, n_y, n_x, i); 
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

void interaction_environnement(int new_pos_y, int new_pos_x, char carte[SIZE_X][SIZE_Y], s_player *Joueur) {
    switch (carte[new_pos_y][new_pos_x])
    {
    //Cases où on peut passer dessus
    case 'O': //Pièce
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
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
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        Joueur->nb_key+=1;
        break;
    case 'H':
        interface_cabane(Joueur);
        break;
    case 'X': //Obstacle
        break;
    case 'P': //Piège
        trap(carte,Joueur,new_pos_y,new_pos_x);
        break;
    //Cases de bases (espace)
    default:
        deplacement(carte,Joueur,new_pos_y,new_pos_x);
        break;
    }
}

void input_player(char carte[SIZE_Y][SIZE_X], s_player *Joueur) {
    char direction = get_char();

    int var_x = 0;
    int var_y = 0;
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
        case 'i': 
            /*if(verif_case(carte,Joueur,'C')) {
                //ouverture_coffre(Joueur);
                RANDOMIZER_SEED;
                int p_or_c = rand()%SIZE_X;
                if(p_or_c %2 == 0) { Joueur->coins += 1;}
                else               { Joueur->life -= 1; }
            }*/
            break;
    }
    int new_pos_x = Joueur->pos_x + var_x;
    int new_pos_y = Joueur->pos_y + var_y;
    interaction_environnement(new_pos_y,new_pos_x,carte,Joueur);
}