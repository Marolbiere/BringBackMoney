#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
//#include <conio.h> 

#define SIZE_X 20
#define SIZE_Y 20

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
    srand(time(NULL));

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
    srand(time(NULL));

    while(lg_buisson_x <= 2) {lg_buisson_x = rand() %6; }
    while(nb_random_y <= 0) {nb_random_y = rand() %SIZE_X-2; }
    
    while(lg_buisson_y <= 2) {lg_buisson_y = rand() %6; }
    //lg_buisson_y = lg_buisson_x;
    int lg_buisson_x_init = lg_buisson_x;

    printw("Buisson : %dX%d\n", lg_buisson_x, lg_buisson_y);

    for (int y = nb_random_y; y < SIZE_Y; y++)
    {
        lg_buisson_x = lg_buisson_x_init;
        for (int x = 0; x < SIZE_X; x++)
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
    srand(time(NULL));
    
    int nb_random_x;
    int nb_piece;

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

void placement_joueur_cabane(char carte[SIZE_X][SIZE_Y]) {
    for (int y = 0; y < SIZE_Y; y++)
    {
        for (int x = 0; x < SIZE_X; x++)
        {
            if(x == SIZE_X - 1 && y == SIZE_Y - 1)
                carte[y][x] = 'H';
            if(x == SIZE_X - 2 && y == SIZE_Y - 1)
                carte[y][x] = 'J';
        }
    }
}

void init_carte(char carte[SIZE_X][SIZE_Y]) { //fonction d'initialisation de carte
    remplissage_espace(carte);
    remplissage_buissons(carte);
    remplissage_obstacle(carte);
    remplissage_piece(carte);
    placement_joueur_cabane(carte);
}