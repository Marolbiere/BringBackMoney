#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
//#include <conio.h> 

#define SIZE_X 20
#define SIZE_Y 20
#define RANDOMIZER_SEED srand(time(NULL))

void remplissage_espace(char carte[SIZE_X][SIZE_Y]){
    for (int y = 0; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++) {
            carte[y][x] = ' ';
        }
    }
}

void remplissage_obstacle(char carte[SIZE_X][SIZE_Y]){
    int nb_random_y = 0;
    int nb_obstacle = 0;
    RANDOMIZER_SEED;

    while(nb_random_y == 0) {nb_random_y = rand() % SIZE_X;    }
    while(nb_obstacle <= 4) {nb_obstacle = rand() %(SIZE_X-3); } //modulo 17

    printw("Nombre d'obstacles : %d\n", nb_obstacle);

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

void remplissage_buissons(char carte[SIZE_X][SIZE_Y]){
    int lg_buisson_x = 0;
    int lg_buisson_y = 0;
    int nb_random_y = 0;
    int nb_random_x = 0;
    RANDOMIZER_SEED;

    while(lg_buisson_x <= 3) {lg_buisson_x = rand() %7; }
    while(lg_buisson_y <= 3) {lg_buisson_y = rand() %7; }
    while(nb_random_y <= 0) {nb_random_y = rand() %SIZE_X-2; }
    while(nb_random_x <= 0) {nb_random_x = rand() %SIZE_X-2; }
    int lg_buisson_x_init = lg_buisson_x;

    printw("Buisson : %dX%d\n", lg_buisson_x, lg_buisson_y);

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

void remplissage_piece(char carte[SIZE_X][SIZE_Y]){
    int nb_random_x;
    int nb_piece;
    RANDOMIZER_SEED;

    while(nb_piece <= 10) { nb_piece = rand() %SIZE_X; }

    printw("Nombre de pieces : %d\n", nb_piece);

    for (int y = 0; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++)
        {
            nb_random_x = rand() % SIZE_X;
            if (nb_random_x == x && nb_piece != 0 && carte[y][x] != 'X' && carte[y][x] != 'G') {
                carte[y][x] = 'O';
                nb_piece-=1;
            }
        }
    }    
}

void remplissage_coffre(char carte[SIZE_X][SIZE_Y]) {
    RANDOMIZER_SEED;
    int nb_random_x;
    int nb_coffre;
    RANDOMIZER_SEED;

    while(nb_coffre <= 1) { nb_coffre = rand() %SIZE_X / 6; }

    printw("Nombre de coffre : %d\n", nb_coffre);

    for (int y = 0; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++)
        {
            nb_random_x = rand() % SIZE_X;
            if (nb_random_x == x && nb_coffre != 0 && carte[y][x] != 'X' && carte[y][x] != 'G' && carte[y][x] != 'O') {
                carte[y][x] = 'C';
                nb_coffre-=1;
            }
        }
    }    
}


void placement_joueur_cabane(char carte[SIZE_X][SIZE_Y]) {
    RANDOMIZER_SEED;
    int nb_random_x = 0;
    int nb_random_y = 0;
    int flag = 1;
    while(carte[nb_random_y][nb_random_x] == 'X' || carte[nb_random_y][nb_random_x] == 'O' || carte[nb_random_y][nb_random_x] == 'G' || carte[nb_random_y][nb_random_x] == 'C' || flag == 1) {
        while(nb_random_x<= 2) {nb_random_x = rand() % SIZE_X - 4;} // entre 2 et 16
        while(nb_random_y<= 2) {nb_random_y = rand() % SIZE_Y - 4;} // entre 2 et 16
        carte[nb_random_y][nb_random_x] = 'H';
        carte[nb_random_y][nb_random_x-1] = 'J';
        flag = 0;
    }
}

void init_carte(char carte[SIZE_X][SIZE_Y]) { //fonction d'initialisation de carte
    remplissage_espace(carte);
    remplissage_buissons(carte);
    remplissage_obstacle(carte);
    remplissage_piece(carte);
    remplissage_coffre(carte);
    placement_joueur_cabane(carte);
}