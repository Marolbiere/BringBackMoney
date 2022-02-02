#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#define SIZE_X 20
#define SIZE_Y 20

void remplissage_espace(char carte[SIZE_Y][SIZE_X]){
    for (int y = 0; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++) {
            carte[y][x] = ' ';
        }
    }
}

void remplissage_obstacle(char carte[SIZE_Y][SIZE_X]){
    RANDOMIZER_SEED;
    int nb_random_y = alea(0,SIZE_X);
    int nb_obstacle = alea(4,SIZE_X - 3);

    //printw("Nombre d'obstacles : %d\n", nb_obstacle);
    for (int y = nb_random_y; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++)
        {
            if(nb_obstacle != 0) {
                carte[y][x] = 'X';
                nb_obstacle-=1;
            }
        }
    }
}

void remplissage_buissons(char carte[SIZE_Y][SIZE_X]){
    RANDOMIZER_SEED;
    int lg_buisson_x = alea(5,7);
    int lg_buisson_y = alea(5,7);
    int nb_random_y = alea(0,SIZE_Y - 3);
    int nb_random_x = alea(0,SIZE_X - 3);

    int lg_buisson_x_init = lg_buisson_x;

    //printw("Buisson : %dX%d\n", lg_buisson_x, lg_buisson_y);

    for (int y = nb_random_y; y < SIZE_Y; y++)
    {
        lg_buisson_x = lg_buisson_x_init;
        for (int x = nb_random_x; x < SIZE_X; x++)
        {
            if(lg_buisson_y !=0 && lg_buisson_x != 0) {
                carte[y][x] = 'G';
                lg_buisson_x-=1;
            }
        }
        if(lg_buisson_y !=0) {
            lg_buisson_y-=1;
        }
    }
}

void remplissage_piece(char carte[SIZE_Y][SIZE_X]){
    RANDOMIZER_SEED;
    int nb_random_x;
    int nb_piece = alea(10, SIZE_X);
    
    while(nb_piece != 0) {
        for (int y = 0; y < SIZE_Y; y++) {
            for (int x = 0; x < SIZE_X; x++) {
                nb_random_x = alea(3,SIZE_X);
                if (nb_random_x == x && nb_piece != 0 && carte[y][x] == ' ') {
                    carte[y][x] = 'O';
                    nb_piece-=1;
                }
            }
        }    
    }
}

void remplissage_coffre_cle(char carte[SIZE_Y][SIZE_X]) {
    RANDOMIZER_SEED;
    int nb_random_x;
    int nb_coffre = alea(2,(SIZE_X/6));

    int nb_key = nb_coffre;
    //printw("Nombre de coffre : %d\n", nb_coffre);

    while(nb_coffre != 0) {
        for (int y = 0; y < SIZE_Y; y++) {
            for (int x = 0; x < SIZE_X; x++) {
                nb_random_x = alea(0,SIZE_X);
                if (nb_random_x == x && nb_coffre != 0 && carte[y][x] != 'X' && carte[y][x] != 'G' && carte[y][x] != 'O') {
                    carte[y][x] = 'C';
                    nb_coffre-=1;
                }
            }
        }
    }

    while(nb_key!=0) {
        for (int y = 0; y < SIZE_Y; y++)
        {
            for (int x = 0; x < SIZE_X; x++)
            {
                nb_random_x = alea(0,SIZE_X);
                if (nb_random_x == x && nb_key != 0 && carte[y][x] != 'X' && carte[y][x] != 'G' && carte[y][x] != 'O' && carte[y][x] != 'C') {
                    carte[y][x] = 'K';
                    nb_key-=1;
                }
            }
        }
    }

}

void placement_piege(char carte[SIZE_Y][SIZE_X]) {
    RANDOMIZER_SEED;
    int nb_random_x;
    int nb_piege = alea(2,5);
    printw("Nombre de piege : %d\n", nb_piege);

    while (nb_piege != 0) {
        for (int y = 0; y < SIZE_Y; y++)
        {
            for (int x = 0; x < SIZE_X; x++)
            {
                nb_random_x = alea(1,SIZE_X);
                if (nb_random_x == x && nb_piege != 0 && carte[y][x] != 'X' && carte[y][x] != 'G' && carte[y][x] != 'C' && carte[y][x] != 'O' && carte[y][x] != 'K' && carte[y][x] != 'H') {
                    carte[y][x] = 'P';
                    nb_piege-=1;
                }
            }
        }
    }
}

void placement_monstre(char carte[SIZE_X][SIZE_X], s_monster tabMonstre[MAX_MONSTER]) {
    RANDOMIZER_SEED;
    int NbMonstre = alea(1,2);
    int TypeMonstre;
    int nb_random_x, nb_random_y;

    for (int i = 0; i < NbMonstre; i++) {
        nb_random_x = alea(2,18);
        nb_random_y = alea(2,18);
        if((i)&&(tabMonstre[0].type == 7 || tabMonstre[0].type == 8))       TypeMonstre = alea(1,2);
        else if((i)&&(tabMonstre[0].type == 3 || tabMonstre[0].type == 4))  TypeMonstre = alea(5,6);
        else                                                                TypeMonstre = alea(1,8);


        while(carte[nb_random_y][nb_random_x] == ' '){
            tabMonstre[i].on_object = 0;
            tabMonstre[i].NbMonstre = NbMonstre;
            tabMonstre[i].type = TypeMonstre;
            tabMonstre[i].pos_x = nb_random_x;
            tabMonstre[i].pos_y = nb_random_y;
            carte[nb_random_y][nb_random_x] = TypeMonstre + '0'; //Affichage ASCII de son Type (Exemple : 1 + '0' = '1')
        }
    }
}

void placement_joueur_cabane(char carte[SIZE_X][SIZE_X], s_player *Joueur) {
    RANDOMIZER_SEED;
    int nb_random_x = 0;
    int nb_random_y = 0;

    do { 
        nb_random_x = alea(2,SIZE_X - 4);
        nb_random_y = alea(2,SIZE_Y - 4);
    } while(carte[nb_random_y][nb_random_x] != ' ');
        
        carte[nb_random_y][nb_random_x] = 'H';
        carte[nb_random_y][nb_random_x-1] = 'J';
        Joueur->pos_x = nb_random_x-1;
        Joueur->pos_y = nb_random_y;
        Joueur->poscab_y = nb_random_y;
        Joueur->poscab_x = nb_random_x;

}

void init_carte(char carte[SIZE_X][SIZE_Y], s_player *Joueur, s_monster TabMonstre[MAX_MONSTER]) { //fonction d'initialisation de carte
    remplissage_espace(carte);
    remplissage_buissons(carte);
    remplissage_obstacle(carte);
    remplissage_piece(carte);
    remplissage_coffre_cle(carte);
    placement_piege(carte);


    placement_monstre(carte, TabMonstre);
    placement_joueur_cabane(carte, Joueur);
}